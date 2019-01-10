//
// Created by eli on 1/9/19.
//

#ifndef EBATTLE_PLANE_BULLET_FACTORY_H
#define EBATTLE_PLANE_BULLET_FACTORY_H

#include "bullet.h"
#include <vector>
#include <string>
#include <memory>
using namespace std;


struct BulletInfo{
   string texturePath;
   unsigned int* _texture;
   float b_width;
   float b_height;
   float attackPower;
};


//TODO 单例模式
class BulletFactory {
public:
    static void loadBullet();
    static shared_ptr<Bullet> getBullet(float _x, float _y ,unsigned int level);
private:
    static vector<BulletInfo> bulletArray;
    static GLuint texID[100];
};


#endif //EBATTLE_PLANE_BULLET_FACTORY_H
