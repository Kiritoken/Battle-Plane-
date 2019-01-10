//
// Created by eli on 1/9/19.
//

#include "bullet.h"
#include <iostream>
#include <GL/glew.h>


Bullet::Bullet(float _x, float _y, float width, float height,unsigned int *_texture)
                                                       :FlyingObject(_x,_y,width,height)
{
    //纹理
    this->texture=_texture;



}

Bullet::~Bullet() {}


void Bullet::move(float _x, float _y) {
    x=_x;
    y=_y;
}

//TODO 碰撞检测
bool Bullet::detectCollision(FlyingObject *flyingObject) {
    return true;
}

void Bullet::render() {
    //启用纹理
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
    //颜色混合模式
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


    switch (direction) {

        default:
            glBegin(GL_QUADS);

            //print();
            //左上
            glTexCoord2f(0.0, 0.0);
            glVertex3f(float(x - f_width * 0.5), float(y + f_height * 0.5), 0.0f);
            //右上
            glTexCoord2f(1.0, 0.0);
            glVertex3f(float(x + f_width * 0.5), float(y + f_height * 0.5), 0.0f);
            //右下
            glTexCoord2f(1.0, 1.0);
            glVertex3f(float(x + f_width * 0.5), float(y - f_height * 0.5), 0.0f);
            //左下
            glTexCoord2f(0.0, 1.0);
            glVertex3f(float(x - f_width * 0.5), float(y - f_height * 0.5), 0.0f);

            glEnd();
            glFlush();

            break;
    }
    move();
}

float Bullet::getX() {
    return x;
}

float Bullet::getY() {
    return y;
}

float Bullet::getVelocity() {
    return velocity;
}

void Bullet::setVelocity(float value) {
    velocity=value;
}

float Bullet::getAcceleration() {
    return acceleration;
}

void Bullet::setAcceleration(float value) {
    acceleration=value;
}

float Bullet::getHp() {
    return HP;
}

void Bullet::setHp(float value) {
    HP=value;
}

float Bullet::getAttackPower() {
    return attackPower;
}

void Bullet::setAttackPower(float value) {
    attackPower=value;
}

void Bullet::addVelocity() {}

void Bullet::addAcceleration() {}

void Bullet::decreaseVelocity() {}

void Bullet::decreaseAcceleration() {}



//TODO 添加斜方向
void Bullet::keyboard_event(int key, int action, int mods) {

}



void Bullet::move() {
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

    //判断是否越界
/*    if(x<-240) x=-240;
    if(x>240) x=240;
    if(y<-320) y=-320;
    if(y>320) y=320;*/
}

