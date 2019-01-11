//
// Created by eli on 1/9/19.
//

#ifndef EBATTLE_PLANE_FLYING_OBJECT_H
#define EBATTLE_PLANE_FLYING_OBJECT_H


#include "../glm/vec2.hpp"

//飞行方向枚举
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


//飞行物种类
enum OBJECT_TYPE{
    PLAER_PLANE,
    PLAYER_BULLET,
    ENEMY_PLANE,
    ENEMY_BULLET
};

//状态枚举
enum STATE{
    ALIVE,   //存活　
    EXPLOED, //爆炸
    DEAD     //出边界
};

class FlyingObject{
public:
    FlyingObject (float _x,float _y,float width,float height, unsigned int _texture_index)
    :x(_x),y(_y),f_width(width),f_height(height),texture_index(_texture_index){

        //包围盒
        left_up=glm::vec2(float(x-f_width*0.5),float(y+f_height*0.5));
        left_down=glm::vec2(float(x-f_width*0.5),float(y-f_height*0.5));
        right_up=glm::vec2(float(x+f_width*0.5),float(y+f_height*0.5));
        right_down=glm::vec2(float(x+f_width*0.5),float(y-f_height*0.5));
    }

    virtual ~FlyingObject();
    //移动
    virtual void move(float _x,float _y) =0;
    virtual void updateBBox()=0;

    //TODO 射击

    //TODO 碰撞检测
    virtual bool detectCollision(FlyingObject *flyingObject)=0;
    virtual bool traverse2DetectCollision()=0;

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

    virtual void setDirection(FLYING_DIRECTION flying_direction)=0;

    virtual void setShootingSpeedInterval(int value)=0;

    virtual STATE getState()=0;
    virtual void  setState(STATE _state)=0;



    OBJECT_TYPE getObjectType(){return objectType;}
    void setObjectType(OBJECT_TYPE type){ objectType=type; }

    /**
     * 键盘
     * @param key
     * @param scancode
     * @param action  GLFW_RELEASE 松开 GLFW_PRESS 按下 GLFW_REPEAT 重复，一直按着
     * @param mods    GLFW_MOD_SHIFT 按下Shift键 GLFW_MOD_CONTROL 按下Ctrl键
     */
    virtual void keyboard_event(int key, int action, int mods)=0;


    //近似包围盒
    glm::vec2 left_up;
    glm::vec2 left_down;
    glm::vec2 right_up;
    glm::vec2 right_down;
protected:
    //纹理贴图索引 GameObject::texID
    unsigned int texture_index;

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
    float HP=10;
    float attackPower=1.0f;


    //射击间隔 间隔shootingSpeedInterval　帧发射　值越小发射速度越快
    int shootingSpeedInterval=20;

    STATE state=ALIVE;
    OBJECT_TYPE objectType=PLAER_PLANE;
};


#endif //EBATTLE_PLANE_FLYING_OBJECT_H
