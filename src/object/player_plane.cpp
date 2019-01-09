//
// Created by eli on 1/9/19.
//

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include "player_plane.h"
#include "../utilis/stb_image.h"


PlayerPlane::PlayerPlane(float _x, float _y, float width, float height):
                        FlyingObject(_x,_y,width,height)
{
    std::string backgroundImage="../res/image/plane1.png";

    glGenTextures(1, &this->texture);
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
}

void PlayerPlane::move(float _x, float _y) {
    x=_x;
    y=_y;
}

//TODO 碰撞检测
bool PlayerPlane::detectCollision(FlyingObject *flyingObject) {
    return true;
}

void PlayerPlane::render() {
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
    glTexCoord2f(0.0,0.0); glVertex3f(float(x-f_width*0.5),float(y+f_height*0.5),0.0f);
    //右上
    glTexCoord2f(1.0,0.0); glVertex3f(float(x+f_width*0.5),float(y+f_height*0.5), 0.0f);
    //右下
    glTexCoord2f(1.0, 1.0); glVertex3f(float(x+f_width*0.5),float(y-f_height*0.5), 0.0f);
    //左下
    glTexCoord2f(0.0,1.0); glVertex3f(float(x-f_width*0.5),float(y-f_height*0.5), 0.0f);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
}

float PlayerPlane::getX() {
    return x;
}

float PlayerPlane::getY() {
    return y;
}

float PlayerPlane::getVelocity() {
    return velocity;
}

void PlayerPlane::setVelocity(float value) {
    velocity=value;
}

float PlayerPlane::getAcceleration() {
    return acceleration;
}

void PlayerPlane::setAcceleration(float value) {
    acceleration=value;
}

float PlayerPlane::getHp() {
    return HP;
}

void PlayerPlane::setHp(float value) {
    HP=value;
}

float PlayerPlane::getAttackPower() {
    return attackPower;
}

void PlayerPlane::setAttackPower(float value) {
    attackPower=value;
}

void PlayerPlane::addVelocity() {}

void PlayerPlane::addAcceleration() {}

void PlayerPlane::decreaseVelocity() {}

void PlayerPlane::decreaseAcceleration() {}


void PlayerPlane::keyboard_event(int key, int action, int mods) {
    if (action == GLFW_PRESS|| action==GLFW_REPEAT){
         switch (key){
         case 'w':case 'W':
             move(x,y+5);
             break;
         case 'a':case 'A':
             move(x-5,y);
             break;
         case 's':case 'S':
             move(x,y-5);
             break;
         case 'd':case 'D':
             move(x+5,y);
             break;
         default:
             break;
         }
    }
}