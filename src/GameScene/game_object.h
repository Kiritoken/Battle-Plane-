//
// Created by eli on 1/10/19.
//

#ifndef EBATTLE_PLANE_GAME_OBJECT_H
#define EBATTLE_PLANE_GAME_OBJECT_H
#include <vector>
#include <memory>
#include "../object/bullet.h"
#include "../object/enemy_plane.h"

using namespace std;

//TODO 单例
class GameObject {
public:
    static vector<shared_ptr<Bullet> > bulletSet;
    static vector<shared_ptr<EnemyPlane> >enemySet;
    static vector<FlyingObject*> flyingObjectSet;

    static void renderBullets();
    static void renderEnemies();
};


#endif //EBATTLE_PLANE_GAME_OBJECT_H
