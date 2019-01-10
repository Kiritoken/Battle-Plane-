//
// Created by eli on 1/9/19.
//

#ifndef EBATTLE_PLANE_BULLET_FACTORY_H
#define EBATTLE_PLANE_BULLET_FACTORY_H
#include <vector>
#include <string>
#include <memory>
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
    static vector<uint > texID;

private:
    static vector<BulletInfo> bulletArray;

};


#endif //EBATTLE_PLANE_BULLET_FACTORY_H
