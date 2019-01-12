//
// Created by eli on 1/10/19.
//

#ifndef EBATTLE_PLANE_GAME_OBJECT_H
#define EBATTLE_PLANE_GAME_OBJECT_H

#include <vector>
#include <memory>
#include <list>
#include "../object/bullet.h"
#include "../object/enemy_plane.h"


using namespace std;

//TODO 单例
class GameObject {
public:
    static vector<shared_ptr<Bullet> > bulletSet;
    static vector<shared_ptr<EnemyPlane> >enemySet;
    static bool clearScreenExceptBoss;


    //TODO 改为基类　List　erase 考虑子弹多了erase效率高
    static list<shared_ptr<FlyingObject> > flyingObjectSet;

    static void renderBullets();
    static void renderEnemies();
    static void renderFlyingObjects();


};


#endif //EBATTLE_PLANE_GAME_OBJECT_H
