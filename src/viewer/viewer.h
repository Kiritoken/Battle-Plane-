//
// Created by eli on 1/8/19.
//

#ifndef EBATTLE_PLANE_VIEWER_H
#define EBATTLE_PLANE_VIEWER_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../GameScene/game_scene.h"
using namespace std;


enum GameState{
    READY,
    PLAYING,
    PAUSE,
    GAMEOVER
};

/**
 * 主窗口显示
 * @author Eli
 * @date 2019/1/8
 */
class Viewer {
public:
    /**
     * 构造函数
     */
    explicit Viewer(std::string title);

    ~Viewer();

    void init();

    void start();

    static void setViewerState(GameState _state){ state=_state; }
private:
    //标题
    std::string _title;


    int fps=0;
    int frameCount=0;
    //时间
    double sys_last;
    double sys_cur;

    //窗口属性
    static GLFWwindow* window;
    static size_t buffer_w;
    static size_t buffer_h;


    static GameState state;
    static GameScene* gameScene;



    /**
    * 循环
    */
    void update(  );

    //事件处理
    static void err_callback( int error, const char* description );
    static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );
    static void resize_callback( GLFWwindow* window, int width, int height );
    static void cursor_callback( GLFWwindow* window, double xpos, double ypos );
    static void scroll_callback( GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_button_callback( GLFWwindow* window, int button, int action, int mods );
};


#endif //EBATTLE_PLANE_VIEWER_H
