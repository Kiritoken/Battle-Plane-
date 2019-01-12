//
// Created by eli on 1/9/19.
//

#include "bullet.h"
#include "../utilis/constant.h"
#include "bullet_factory.h"
#include "../GameScene/game_object.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>



Bullet::Bullet(float _x, float _y, float width, float height,unsigned int _texture_index)
                                                       :FlyingObject(_x,_y,width,height,_texture_index)
{
    updateBBox();
}

Bullet::~Bullet() {
    //delete texture;
   // std::cout<<"被析构"<<std::endl;
}


void Bullet::move(float _x, float _y) {
    x=_x;
    y=_y;
    updateBBox();
}

//TODO 碰撞检测
bool Bullet::detectCollision(FlyingObject *flyingObject) {
    glm::vec2 p1=flyingObject->left_up;
    glm::vec2 p2=flyingObject->right_down;

    glm::vec2 p3=this->left_up;
    glm::vec2 p4=this->right_down;


    if(!(p2.x<p3.x || p2.y>p3.y || p1.x>p4.x || p1.y <p4.y)){
        //碰撞
        return true;
    }else{
        return false;
    }
}

void Bullet::render() {
    if(state==DEAD)
        return;

    if(this->HP<=0.0f){
        this->setState(DEAD);
        return;
    }


    //判断是否出界面
    if(!(Constant::screenHeight*0.5>right_down.y && -Constant::screenHeight*0.5<left_up.y&&
       -Constant::screenWidth*0.5<right_down.x && Constant::screenWidth>left_up.x))
   {
       this->setState(DEAD);
       return;
   }


    //只需要player_bullet进行碰撞检测
    if(this->objectType==PLAYER_BULLET&&traverse2DetectCollision()){
        this->setState(DEAD);
        return;
    }


    //启用纹理
    glEnable(GL_TEXTURE_2D);
    if(this->objectType==ENEMY_BULLET){
        glBindTexture(GL_TEXTURE_2D, BulletFactory::enemyTexID[texture_index]);
    }else {
        glBindTexture(GL_TEXTURE_2D, BulletFactory::texID[texture_index]);
    }
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



//TODO 子弹测试
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

/*    if(this->getObjectType()==ENEMY_BULLET) {
        //TODO 子弹随机方向测试
        srand((unsigned)time(NULL));
        int  _direction=(rand()%(RIGHT_DOWN-STOP+1))+STOP;
        cout<<_direction<<endl;
        this->setDirection(static_cast<FLYING_DIRECTION >(_direction));
    }*/

    //更新包围盒
    updateBBox();
}



void Bullet::updateBBox() {
    left_up=glm::vec2(float(x-f_width*0.5),float(y+f_height*0.5));
    left_down=glm::vec2(float(x-f_width*0.5),float(y-f_height*0.5));
    right_up=glm::vec2(float(x+f_width*0.5),float(y+f_height*0.5));
    right_down=glm::vec2(float(x+f_width*0.5),float(y-f_height*0.5));
}



bool Bullet::traverse2DetectCollision() {
    for(auto &shared_ptr_object:GameObject::flyingObjectSet){
        auto type=shared_ptr_object->getObjectType();
        //跳过自己 和PLAYER_PLANE ENEMY_BULLET
        if(shared_ptr_object.get()==this || type==this->getObjectType()||type==PLAER_PLANE ||type==ENEMY_BULLET ||type==EXPLOSION){
            continue;
        }

        //如果与敌机碰撞
        if(this->detectCollision(shared_ptr_object.get())){
            shared_ptr_object->setHp(shared_ptr_object->getHp()-this->attackPower);
            return true;
        }
    }
    return false;
}