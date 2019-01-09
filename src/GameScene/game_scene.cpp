//
// Created by eli on 1/8/19.
//
#define STB_IMAGE_IMPLEMENTATION
#include "../utilis/stb_image.h"
#include "game_scene.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GameScene::GameScene() {

}

void GameScene::init(int width, int height) {
    backgroundImage="../res/image/background6.bmp";
    this->width=width/2;
    this->height=height/2;

    //速度
    velocity=0.001;
    //加速度
    //acceleration=0.00001;
    acceleration=0;
    reset_uv();

    glGenTextures(1, &texture);
    //绑定纹理
    glBindTexture(GL_TEXTURE_2D, texture);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    int i_width, i_height, nrChannels;
    unsigned char *data = stbi_load(backgroundImage.c_str(), &i_width, &i_height, &nrChannels, 4);
    if (data){
        //生成纹理
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA8, i_width, i_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "背景图片加载失败" << std::endl;
    }
    stbi_image_free(data);

    std::cout<<"初始化战机中......"<<std::endl;
    playerPlane=new PlayerPlane(0,0,82,82);
    std::cout<<"战机初始化完毕"<<std::endl;
}

GameScene::~GameScene() {
   delete playerPlane;
}

void GameScene::render() {
    //启用纹理
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    //颜色混合模式
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBegin(GL_QUADS);
    /**
     * UV 纹理坐标系，原点在坐上　ｘ轴向右　ｙ轴向下
     *
     */
    //print();
    //左上
    glTexCoord2f(left_up.x, left_up.y); glVertex3f(-width,height,0.0f);
    //右上
    glTexCoord2f(right_up.x, right_up.y); glVertex3f(width, height, 0.0f);
    //右下
    glTexCoord2f(right_down.x, right_down.y); glVertex3f(width, -height, 0.0f);
    //左下
    glTexCoord2f(left_down.x, left_down.y); glVertex3f(-width, -height, 0.0f);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    update_uv();

    playerPlane->render();
}

void GameScene::update_uv() {
    float distance=unit_distance();
    if(left_up.y>1.0)
        reset_uv();
    left_down.y+=distance;
    right_down.y+=distance;
    left_up.y+=distance;
    right_up.y+=distance;
}



void GameScene::reset_uv() {
/*    left_up=glm::vec2(0.0,0.0);
    right_up=glm::vec2(float(width)/1000,0.0);
    right_down=glm::vec2(float(width)/1000,float(height)/1000);
    left_down=glm::vec2(0.0,float(height)/1000);*/

    left_up=glm::vec2(0.0,0.0);
    right_up=glm::vec2(1.0,0.0);
    right_down=glm::vec2(1.0,float(height)/1000);
    left_down=glm::vec2(0.0,float(height)/1000);
}


void GameScene::print() {
    std::cout<<left_up.x<<" "<<left_up.y<<" ";
    std::cout<<right_up.x<<" "<<right_up.y<<" ";
    std::cout<<right_down.x<<" "<<right_down.y<<" ";
    std::cout<<left_down.x<<" "<<left_down.y<<std::endl;
}


//单位时间内的位移
float GameScene::unit_distance() {
    //位移
    float distance;

    //匀速 velocity*t
    if(acceleration==0){
        distance = velocity;
    }else{
        distance=float(velocity+0.5*acceleration);
        //更新速度
        velocity+=acceleration;
    }
    if(velocity<=0){
        velocity=0;
        acceleration=0;
    }
    return distance;
}


void GameScene::keyboard_event(int key, int action, int mods) {
    if (action == GLFW_PRESS){
        if(key==GLFW_KEY_PAGE_UP){
           addVelocity();
        }else if(key==GLFW_KEY_PAGE_DOWN){
            decreaseVelocity();
        }else if(key==GLFW_KEY_HOME){
            addAcceration();
        }else if(key==GLFW_KEY_END){
            decreaseAcceration();
        }
    }
    playerPlane->keyboard_event(key,action,mods);
}