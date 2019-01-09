//
// Created by eli on 1/9/19.
//

#ifndef EBATTLE_PLANE_FLYING_OBJECT_H
#define EBATTLE_PLANE_FLYING_OBJECT_H


enum FLYING_DIRECTION{
    LEFT,
    UP,
    LEFT_UP,
    RIGHT,
    DOWN,
    RIGHT_UP,
    LEFT_DOWN,
    RIGHT_DOWN,
    STOP
};


class FlyingObject{
public:
    FlyingObject (float _x,float _y,float width,float height):x(_x),y(_y),
                                                f_width(width),f_height(height){}
    //移动
    virtual void move(float _x,float _y) =0;

    //TODO 射击

    //TODO 碰撞检测
    virtual bool detectCollision(FlyingObject *flyingObject)=0;

    //绘制
    virtual void render()=0;

    virtual float getX()=0;
    virtual float getY()=0;

    virtual float getVelocity()=0;
    virtual void  setVelocity(float value)=0;

    virtual float getAcceleration()=0;
    virtual void  setAcceleration(float value)=0;

    virtual float getHp()=0;
    virtual void setHp(float value)=0;

    virtual float getAttackPower()=0;
    virtual void  setAttackPower(float value)=0;

    //控制速度＆加速度
    virtual void addVelocity()=0;
    virtual void decreaseVelocity()=0;
    virtual void addAcceleration()=0;
    virtual void decreaseAcceleration()=0;

    /**
     * 键盘
     * @param key
     * @param scancode
     * @param action  GLFW_RELEASE 松开 GLFW_PRESS 按下 GLFW_REPEAT 重复，一直按着
     * @param mods    GLFW_MOD_SHIFT 按下Shift键 GLFW_MOD_CONTROL 按下Ctrl键
     */
    virtual void keyboard_event(int key, int action, int mods)=0;
protected:
    //纹理贴图
    unsigned int texture;

    //中心坐标
    float x;
    float y;

    //飞行物大小
    float f_width;
    float f_height;

    FLYING_DIRECTION direction=STOP;
    //速度与加速度
    float velocity=5;
    float acceleration=0;

    //ＨＰ　＆　Attack Power
    float HP;
    float attackPower;
};


#endif //EBATTLE_PLANE_FLYING_OBJECT_H
