//
// Created by eli on 1/11/19.
//

#ifndef EBATTLE_PLANE_EXPLOSION_FACTORY_H
#define EBATTLE_PLANE_EXPLOSION_FACTORY_H
#include <iostream>
#include <vector>
#include <memory>
#include "flying_object.h"


using namespace std;

struct ExplosionInfo{
    string texturePath;
    unsigned int texture_index;//纹理索引
    float b_width;
    float b_height;
};

//前向声明
class Explosion;
class ExplosionFactory {
public:
    static void loadExplosion();
    static shared_ptr<Explosion> getExplosion(float _x, float _y ,float _width,float _height,float _velocity,float _acceleration,FLYING_DIRECTION _direction);
    static vector<uint > texID;

    static vector<ExplosionInfo> explosionArray;
};


#endif //EBATTLE_PLANE_EXPLOSION_FACTORY_H
