//
// Created by eli on 1/10/19.
//

#include "game_object.h"

vector<Bullet*> GameObject::bulletSet;
vector<FlyingObject*> GameObject::flyingObjectSet;




//渲染player发射的子弹
void GameObject::renderBullets() {
    //正确的遍历方法
    for(auto iter_bullet=bulletSet.begin();iter_bullet!=bulletSet.end(); ){
        (*iter_bullet)->render();
        //超出边界 析构
        if((*iter_bullet)->getState()==DEAD){
            //delete *iter_bullet;
            iter_bullet=bulletSet.erase(iter_bullet);
        } else{
            iter_bullet++;
        }
    }
}