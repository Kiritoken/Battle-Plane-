//
// Created by eli on 1/8/19.
//

#ifndef EBATTLE_PLANE_GAME_SCENE_H
#define EBATTLE_PLANE_GAME_SCENE_H
#include <string>
#include <vector>
#include "../glm/glm.hpp"

class GameScene {
public:
    GameScene(int width,int height);
    ~GameScene();
    void render();

    //设定速度＆加速度
    float getVelocity() { return velocity; }
    void setVelovity(float value){ velocity=value>0 ? value:0; }
    float getAcceleration() { return acceleration;}
    void setAcceleration(float value) {acceleration=value;}
private:
    std::string backgroundImage;
    unsigned int texture;

    //UV
    glm::vec2 left_up;
    glm::vec2 right_up;
    glm::vec2 right_down;
    glm::vec2 left_down;

    int width;
    int height;

    //速度
    float velocity;
    //加速度
    float acceleration;

    void reset_uv();
    void update_uv();
    void print();

    //计算单位时间内的位移
    float unit_distance();
};


#endif //EBATTLE_PLANE_GAME_SCENE_H
