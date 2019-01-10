//
// Created by eli on 1/9/19.
//

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <cmath>
#include "player_plane.h"
#include "../utilis/stb_image.h"
#include "bullet_factory.h"
#include "../GameScene/game_object.h"
//默认窗口大小
#define DEFAULT_W 480
#define DEFAULT_H 640
#define PI 3.1415927

PlayerPlane::PlayerPlane(float _x, float _y, float width, float height):
                        FlyingObject(_x,_y,width,height)
{
    std::string backgroundImage="../res/image/plane23.png";

    glGenTextures(1, this->texture);
    //绑定纹理
    glBindTexture(GL_TEXTURE_2D, *texture);
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

    setVelocity(10);
    setShootingSpeedInterval(2);
   //setAcceleration(1.0);

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
    glBindTexture(GL_TEXTURE_2D, *texture);
    //颜色混合模式
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

   switch (direction) {
 /*      case LEFT:
       case LEFT_DOWN:
       case LEFT_UP:
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glTranslatef(0.5, 0.5, 0.0);
        glRotatef(90, 0, 0.0, 1.0);
        glBegin(GL_QUADS);

        *//**
        * UV 纹理坐标系，原点在坐上　ｘ轴向右　ｙ轴向下
        *
        *//*
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
        glPopMatrix();

        glFlush();
        glDisable(GL_TEXTURE_2D);
     break;

       case RIGHT:
       case RIGHT_DOWN:
       case RIGHT_UP:
           glMatrixMode(GL_TEXTURE);
           glLoadIdentity();
           glMatrixMode(GL_MODELVIEW);

           glPushMatrix();
           glTranslatef(0.5, 0.5, 0.0);
           glRotatef(-90, 0, 0.0, 1.0);
           glBegin(GL_QUADS);

           *//**
           * UV 纹理坐标系，原点在坐上　ｘ轴向右　ｙ轴向下
           *
           *//*
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
           glPopMatrix();

           glFlush();
           glDisable(GL_TEXTURE_2D);
       break;*/
       default:
           glBegin(GL_QUADS);

           //print();
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
    //移动
    move();

    //射击
    shootBullet();
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



//TODO 添加斜方向
void PlayerPlane::keyboard_event(int key, int action, int mods) {

    if (action == GLFW_PRESS|| action==GLFW_REPEAT){
     //   std::cout<<"按下"<<char(key)<<std::endl;
       if(key=='W'||key=='A'||key=='S'||key=='D'||key=='J')
        pressed[key]=true;
    }
    //松开
    if(action==GLFW_RELEASE){
        pressed[key]=false;
     //   std::cout<<"松开"<<key<<std::endl;
    }
    confirmDirection();
}

void PlayerPlane::confirmDirection() {
    bool bL=pressed['A'];
    bool bR=pressed['D'];
    bool bU=pressed['W'];
    bool bD=pressed['S'];
    //射击状态
    shooting=pressed['J'];

    if(bL && !bU && !bR && !bD) direction = LEFT;
    else if(bL && bU && !bR && !bD) direction = LEFT_UP;
    else if(!bL && bU && !bR && !bD) direction = UP;
    else if(!bL && bU && bR && !bD) direction = RIGHT_UP;
    else if(!bL && !bU && bR && !bD) direction = RIGHT;
    else if(!bL && !bU && bR && bD) direction = RIGHT_DOWN;
    else if(!bL && !bU && !bR && bD) direction = DOWN;
    else if(bL && !bU && !bR && bD) direction = LEFT_DOWN;
    else if(!bL && !bU && !bR && !bD) direction = STOP;

    //std::cout<<direction<<std::endl;
}


void PlayerPlane::move() {
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
          //  std::cout<<"左上"<<std::endl;
            distance_x=float((velocity+0.5*acceleration)*0.707106781);
            distance_y=distance_x;
            x-=distance_x;
            y+=distance_y;
            velocity+=acceleration;
            break;
        case LEFT_DOWN:
           // std::cout<<"左下"<<std::endl;
            distance_x=float((velocity+0.5*acceleration)*0.707106781);
            distance_y=distance_x;
            x-=distance_x;
            y-=distance_y;
            velocity+=acceleration;
            break;
        case RIGHT_UP:
          //  std::cout<<"右上"<<std::endl;
            distance_x=float((velocity+0.5*acceleration)*0.707106781);
            distance_y=distance_x;
            x+=distance_x;
            y+=distance_y;
            velocity+=acceleration;
            break;
        case RIGHT_DOWN:
           // std::cout<<"右下"<<std::endl;
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
    if(x<-240) x=-240;
    if(x>240) x=240;
    if(y<-320) y=-320;
    if(y>320) y=320;
    updateBBox();
}


void PlayerPlane::shootBullet() {
    static int frameCount=0;
    //cout<<frameCount<<endl;
    if(shooting){
        if(shootingSpeedInterval<=frameCount) {
            //new bullet 添加到ＧameScene中去
            auto bullet = BulletFactory::getBullet(x, float(y + f_height * 0.5), 6);
            if (bullet) {
                bullet->setDirection(UP);
                GameObject::bulletSet.push_back(bullet);
            }
            frameCount=0;
        }
    }
    frameCount++;
    if(frameCount==60){
        frameCount=0;
    }
}



void PlayerPlane::updateBBox() {
    left_up=glm::vec2(float(x-f_width*0.5),float(y+f_height*0.5));
    left_down=glm::vec2(float(x-f_width*0.5),float(y-f_height*0.5));
    right_up=glm::vec2(float(x+f_width*0.5),float(y+f_height*0.5));
    right_down=glm::vec2(float(x+f_width*0.5),float(y-f_height*0.5));
}