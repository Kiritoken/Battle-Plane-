//
// Created by eli on 1/10/19.
//

#include <iostream>
#include <GL/glew.h>
#include "enemy_plane.h"
#include "../utilis/constant.h"
#include "enemy_factory.h"


EnemyPlane::EnemyPlane(float _x, float _y, float width, float height,unsigned int _texture_index)
        :FlyingObject(_x,_y,width,height,_texture_index)
{
    updateBBox();
}

EnemyPlane::~EnemyPlane() {
    // std::cout<<"被析构"<<std::endl;
}


void EnemyPlane::move(float _x, float _y) {
    x=_x;
    y=_y;
}

//TODO 碰撞检测
bool EnemyPlane::detectCollision(FlyingObject *flyingObject) {
    return true;
}

void EnemyPlane::render() {

    //判断是否出界面 要大一圈
    if(!(Constant::screenHeight*0.5+f_height>right_down.y && -Constant::screenHeight*0.5-f_height<left_up.y&&
         -Constant::screenWidth*0.5-f_width<right_down.x && Constant::screenWidth+f_width>left_up.x))
    {
        setState(DEAD);
        return;
    }

   //cout<<"绘制敌机"<<endl;
    //启用纹理
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, EnemyFactory::texID[texture_index]);
    //颜色混合模式
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


    switch (direction) {
        default:
            glBegin(GL_QUADS);
            //左上
            glTexCoord2f(0.0, 0.0);
            glVertex3f(left_up.x,left_up.y ,0.0f);
            //右上
            glTexCoord2f(1.0, 0.0);
            glVertex3f(right_up.x,right_up.y ,0.0f);
            //右下
            glTexCoord2f(1.0, 1.0);
            glVertex3f(right_down.x,right_down.y, 0.0f);
            //左下
            glTexCoord2f(0.0, 1.0);
            glVertex3f(left_down.x,left_down.y,0.0f);
            glEnd();
            glFlush();
            break;
    }
    move();
}

float EnemyPlane::getX() {
    return x;
}

float EnemyPlane::getY() {
    return y;
}

float EnemyPlane::getVelocity() {
    return velocity;
}

void EnemyPlane::setVelocity(float value) {
    velocity=value;
}

float EnemyPlane::getAcceleration() {
    return acceleration;
}

void EnemyPlane::setAcceleration(float value) {
    acceleration=value;
}

float EnemyPlane::getHp() {
    return HP;
}

void EnemyPlane::setHp(float value) {
    HP=value;
}

float EnemyPlane::getAttackPower() {
    return attackPower;
}

void EnemyPlane::setAttackPower(float value) {
    attackPower=value;
}

void EnemyPlane::addVelocity() {}

void EnemyPlane::addAcceleration() {}

void EnemyPlane::decreaseVelocity() {}

void EnemyPlane::decreaseAcceleration() {}




void EnemyPlane::keyboard_event(int key, int action, int mods) {
}



void EnemyPlane::move() {
    //x轴位移
    float distance_x;
    //y轴位移
    float distance_y;
    switch(direction){
        case LEFT:
            distance_x=float(velocity+0.5*acceleration);
            //更新速度
            velocity+=acceleration;
            x-=distance_x;
            break;
        case RIGHT:
            distance_x=float(velocity+0.5*acceleration);
            //更新速度
            velocity+=acceleration;
            x+=distance_x;
            break;
        case UP:
            distance_y=float(velocity+0.5*acceleration);
            velocity+=acceleration;
            y+=distance_y;
            break;
        case DOWN:
            distance_y=float(velocity+0.5*acceleration);
            velocity+=acceleration;
            y-=distance_y;
            break;
        case LEFT_UP:
            std::cout<<"左上"<<std::endl;
            distance_x=float((velocity+0.5*acceleration)*0.707106781);
            distance_y=distance_x;
            x-=distance_x;
            y+=distance_y;
            velocity+=acceleration;
            break;
        case LEFT_DOWN:
            std::cout<<"左下"<<std::endl;
            distance_x=float((velocity+0.5*acceleration)*0.707106781);
            distance_y=distance_x;
            x-=distance_x;
            y-=distance_y;
            velocity+=acceleration;
            break;
        case RIGHT_UP:
            std::cout<<"右上"<<std::endl;
            distance_x=float((velocity+0.5*acceleration)*0.707106781);
            distance_y=distance_x;
            x+=distance_x;
            y+=distance_y;
            velocity+=acceleration;
            break;
        case RIGHT_DOWN:
            std::cout<<"右下"<<std::endl;
            distance_x=float((velocity+0.5*acceleration)*0.707106781);
            distance_y=distance_x;
            x+=distance_x;
            y-=distance_y;
            velocity+=acceleration;
            break;
        case STOP:
            velocity=10;
            break;
    }
    //更新包围盒
    updateBBox();
}



void EnemyPlane::updateBBox() {
    left_up=glm::vec2(float(x-f_width*0.5),float(y+f_height*0.5));
    left_down=glm::vec2(float(x-f_width*0.5),float(y-f_height*0.5));
    right_up=glm::vec2(float(x+f_width*0.5),float(y+f_height*0.5));
    right_down=glm::vec2(float(x+f_width*0.5),float(y-f_height*0.5));
}