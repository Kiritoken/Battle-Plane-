//
// Created by eli on 1/11/19.
//

#include <GL/glew.h>
#include "explosion.h"
#include "../utilis/constant.h"
#include "explosion_factory.h"
#include "../GameScene/game_object.h"

Explosion::Explosion(float _x, float _y, float width, float height,unsigned int _texture_index)
        :FlyingObject(_x,_y,width,height,_texture_index)
{
    this->setObjectType(EXPLOSION);
    updateBBox();
}

Explosion::~Explosion() {
    //delete texture;
    // std::cout<<"被析构"<<std::endl;
}


void Explosion::move(float _x, float _y) {
    x=_x;
    y=_y;
}

//TODO 碰撞检测
bool Explosion::detectCollision(FlyingObject *flyingObject) {
     return false;

}

void Explosion::render() {
    if(state==DEAD)
        return;

    //判断是否出界面
    if(!(Constant::screenHeight*0.5>right_down.y && -Constant::screenHeight*0.5<left_up.y&&
         -Constant::screenWidth*0.5<right_down.x && Constant::screenWidth>left_up.x))
    {
        this->setState(DEAD);
        return;
    }


    //渲染完爆炸效果
    if(texture_index>=ExplosionFactory::explosionArray.size()){
        this->setState(DEAD);
        return;
    }
    //启用纹理
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ExplosionFactory::texID[texture_index]);
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

    this->texture_index++;
    move();
}

float Explosion::getX() {
    return x;
}

float Explosion::getY() {
    return y;
}

float Explosion::getVelocity() {
    return velocity;
}

void Explosion::setVelocity(float value) {
    velocity=value;
}

float Explosion::getAcceleration() {
    return acceleration;
}

void Explosion::setAcceleration(float value) {
    acceleration=value;
}

float Explosion::getHp() {
    return HP;
}

void Explosion::setHp(float value) {
    HP=value;
}

float Explosion::getAttackPower() {
    return attackPower;
}

void Explosion::setAttackPower(float value) {
    attackPower=value;
}

void Explosion::addVelocity() {}

void Explosion::addAcceleration() {}

void Explosion::decreaseVelocity() {}

void Explosion::decreaseAcceleration() {}



//TODO 子弹测试
void Explosion::keyboard_event(int key, int action, int mods) {
}



void Explosion::move() {
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
            distance_x=float((velocity+0.5*acceleration)*0.707106781);
            distance_y=distance_x;
            x-=distance_x;
            y+=distance_y;
            velocity+=acceleration;
            break;
        case LEFT_DOWN:
            distance_x=float((velocity+0.5*acceleration)*0.707106781);
            distance_y=distance_x;
            x-=distance_x;
            y-=distance_y;
            velocity+=acceleration;
            break;
        case RIGHT_UP:
            distance_x=float((velocity+0.5*acceleration)*0.707106781);
            distance_y=distance_x;
            x+=distance_x;
            y+=distance_y;
            velocity+=acceleration;
            break;
        case RIGHT_DOWN:
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



void Explosion::updateBBox() {
    left_up=glm::vec2(float(x-f_width*0.5),float(y+f_height*0.5));
    left_down=glm::vec2(float(x-f_width*0.5),float(y-f_height*0.5));
    right_up=glm::vec2(float(x+f_width*0.5),float(y+f_height*0.5));
    right_down=glm::vec2(float(x+f_width*0.5),float(y-f_height*0.5));
}



bool Explosion::traverse2DetectCollision() {
    return false;
}