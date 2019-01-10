//
// Created by eli on 1/9/19.
//

#ifndef EBATTLE_PLANE_BULLET_H
#define EBATTLE_PLANE_BULLET_H


#include "flying_object.h"
#include "../glm/vec2.hpp"
#include "bullet_factory.h"

class Bullet : public FlyingObject{
public:
    //构造函数
    Bullet(float _x,float _y,float width,float height,unsigned int _texture_index);

    ~Bullet() override;
    //移动
    void move(float _x,float _y) override;

    void move();

    //TODO 射击

    //TODO 碰撞检测
    bool detectCollision(FlyingObject *flyingObject) override;

    //绘制
    void render() override;

    float getX() override;
    float getY() override;

    float getVelocity() override;
    void  setVelocity (float value)override;

    float getAcceleration()override;
    void  setAcceleration(float value)override;

    float getHp()override;
    void  setHp(float value)override;

    float getAttackPower()override;
    void  setAttackPower(float value)override;

    //控制速度＆加速度
    void addVelocity()override;
    void decreaseVelocity()override;
    void addAcceleration()override;
    void decreaseAcceleration()override;

    void keyboard_event(int key, int action, int mods) override;
    void setDirection(FLYING_DIRECTION flying_direction) override {direction=flying_direction; }

    void setShootingSpeedInterval(int value) override{shootingSpeedInterval=value; }

    STATE getState() override{ return state; }
    void  setState(STATE _state) override{ state=_state; }
    void updateBBox() override;

    //bool frinedly;

private:
};


#endif //EBATTLE_PLANE_BULLET_H
