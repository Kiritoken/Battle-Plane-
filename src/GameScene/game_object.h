//
// Created by eli on 1/10/19.
//

#ifndef EBATTLE_PLANE_GAME_OBJECT_H
#define EBATTLE_PLANE_GAME_OBJECT_H
#include <vector>
#include "../object/bullet.h"

using namespace std;

//TODO 单例
class GameObject {
public:
    static vector<Bullet*> bulletSet;
    static vector<FlyingObject*> flyingObjectSet;
    static void renderBullets();
};


#endif //EBATTLE_PLANE_GAME_OBJECT_H
