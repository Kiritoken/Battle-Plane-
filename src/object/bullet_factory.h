//
// Created by eli on 1/9/19.
//

#ifndef EBATTLE_PLANE_BULLET_FACTORY_H
#define EBATTLE_PLANE_BULLET_FACTORY_H
#include <vector>
#include <string>
#include <memory>
#include "../utilis/constant.h"
using namespace std;


struct BulletInfo{
   string texturePath;
   unsigned int texture_index;//纹理索引
   float b_width;
   float b_height;
   float attackPower;
};




class Bullet;

//TODO 单例模式
class BulletFactory {
public:
    static void loadBullet();
    static shared_ptr<Bullet> getBullet(float _x, float _y ,unsigned int level);
    //根据坐标随机产生子弹
    static void genBulletsByPos(float x_min,float x_max,float y,float _velocity,float acceleration);
    static vector<uint> texID;
    static vector<uint> enemyTexID;

private:
    static vector<BulletInfo> bulletArray;

    //敌人子弹纹理
    static vector<BulletInfo> enemyBulletArray;
};


#endif //EBATTLE_PLANE_BULLET_FACTORY_H
