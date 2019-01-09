//
// Created by eli on 1/8/19.
//
#include <iostream>
#include "viewer.h"
using namespace std;
//默认窗口大小
#define DEFAULT_W 480
#define DEFAULT_H 640

// window properties
GLFWwindow* Viewer::window;
size_t Viewer::buffer_w;
size_t Viewer::buffer_h;

GameState Viewer::state=READY;
GameScene* Viewer::gameScene=new GameScene();


Viewer::Viewer(std::string title):_title(title){}

//析构函数
Viewer::~Viewer() {
    glfwDestroyWindow(window);
    glfwTerminate();

    //TODO 释放堆上空间
    delete gameScene;
}


//初始化
void Viewer::init() {
    glfwSetErrorCallback( err_callback );
    if( !glfwInit() ) {
        cerr<<"ＧLFW未能初始化!"<<endl;
        exit( 1 );
    }

    //窗口大小不可resize
    glfwWindowHint(GLFW_RESIZABLE , GL_FALSE );
    //创建窗口
    window = glfwCreateWindow( DEFAULT_W, DEFAULT_H, _title.c_str(), nullptr, nullptr);
    if (!window) {
        cerr<<"窗口初始化失败"<<endl;
        glfwTerminate();
        exit( 1 );
    }

    //set context
    glfwMakeContextCurrent( window );
    glfwSwapInterval(1);

    //注册回调事件
    // framebuffer event callbacks
    glfwSetFramebufferSizeCallback( window, resize_callback );

    //注册盘回调函数
    glfwSetKeyCallback( window, key_callback );

    //指针回调
    glfwSetCursorPosCallback( window, cursor_callback );

    //滚轮
    glfwSetScrollCallback(window, scroll_callback);

    //鼠标
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr<<"G　l　e　w　初始化失败!"<<endl;
        glfwTerminate();
        exit( 1 );
    }

    // enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport( 0 ,0 , DEFAULT_W , DEFAULT_H );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-DEFAULT_W/2,DEFAULT_W/2,-DEFAULT_H/2,DEFAULT_H/2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    // resize components to current window size, get DPI
    glfwGetFramebufferSize(window, (int*) &buffer_w, (int*) &buffer_h );

    //TODO　初始化GameScene

    // resize elements to current size
    resize_callback(window, (int)buffer_w, (int)buffer_h);

    gameScene->init(DEFAULT_W,DEFAULT_H);
    state=READY;
}


void Viewer::start() {
    while( !glfwWindowShouldClose( window ) ) {
        update();
    }
}


//帧渲染
void Viewer::update() {
    //清空颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //背景色
    glClearColor(1.0,1.0,1.0,0.0);

    //TODO 游戏场景渲染&游戏逻辑
    switch (state){
        case READY:
          //  cout<<"READY"<<endl;
            break;
        case PLAYING:
           // cout<<"PLAYING"<<endl;
           gameScene->render();
            break;
        case PAUSE:
            //cout<<"PAUSE"<<endl;
            break;
        case GAMEOVER:
           // cout<<"GAMEOVER"<<endl;
            break;
    }



    //swap buffers
    glfwSwapBuffers(window);

    // poll events
    glfwPollEvents();
}


void Viewer::err_callback( int error, const char* description ) {
    cerr<<"Error: "<<description<<endl;
}

void Viewer::resize_callback( GLFWwindow* window, int width, int height ) {
    //get framebuffer size
    int w, h;
    glfwGetFramebufferSize(window, &w, &h );

    // update buffer size
    buffer_w = w; buffer_h = h;
    glViewport( 0, 0, buffer_w, buffer_h );
}

void Viewer::cursor_callback( GLFWwindow* window, double xpos, double ypos ) {}

void Viewer::scroll_callback( GLFWwindow* window, double xoffset, double yoffset) {}


void Viewer::mouse_button_callback( GLFWwindow* window, int button, int action, int mods ) {
    //TODO
  //  enderer->mouse_event( button, action, mods );
}



/**
 * @param window
 * @param key 按键
 * @param scancode
 * @param action GLFW_RELEASE 松开 GLFW_PRESS 按下 GLFW_REPEAT 重复，一直按着
 * @param mods GLFW_MOD_SHIFT 按下Shift键 GLFW_MOD_CONTROL 按下Ctrl键
 */
void Viewer::key_callback( GLFWwindow* window,int key, int scancode, int action, int mods ) {
    //键盘按下
    if (action == GLFW_PRESS) {
        if( key == GLFW_KEY_ESCAPE ) {
            glfwSetWindowShouldClose( window, true );
        }
        if(key == GLFW_KEY_ENTER && state==READY)
            state=PLAYING;
        if(key == GLFW_KEY_P) {
            state = PAUSE;
            return;
        }
    }

    //TODO 游戏逻辑处理
   gameScene->keyboard_event( key, action, mods );
}