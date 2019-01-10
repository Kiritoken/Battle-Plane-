//
// Created by eli on 1/10/19.
//

#ifndef EBATTLE_PLANE_ENEMY_FACTORY_H
#define EBATTLE_PLANE_ENEMY_FACTORY_H

#include <vector>
#include <string>
#include <memory>
using namespace std;


struct EnemyInfo{
    string texturePath;
    unsigned int texture_index;//纹理索引
    float b_width;
    float b_height;
    float attackPower;
    //TODO JSON 读取　
};


class EnemyPlane;

class EnemyFactory {
public:
    static void loadEnemyPlane();
    static shared_ptr<EnemyPlane> getEnemyPlane(float _x, float _y ,unsigned int level);
    static void genEnemyPlanes();
    static vector<uint > texID;

private:
    static vector<EnemyInfo> enemyPlaneArray;
};


#endif //EBATTLE_PLANE_ENEMY_FACTORY_H
