//
// Created by eli on 1/8/19.
//

#ifndef EBATTLE_PLANE_GAME_SCENE_H
#define EBATTLE_PLANE_GAME_SCENE_H
#include <string>
#include <vector>
#include "../glm/glm.hpp"
#include "../object/player_plane.h"


class GameScene {
public:
    GameScene();
    ~GameScene();

    void init(int width,int height);
    void render();

    //设定速度＆加速度
    float getVelocity() { return velocity; }
    void setVelovity(float value){ velocity=value>0 ? value:0; }
    float getAcceleration() { return acceleration;}
    void setAcceleration(float value) {acceleration=value;}

    void addVelocity(){ velocity+=0.0001; }
    void decreaseVelocity(){ velocity-=0.0001; }
    void addAcceration(){ acceleration+=0.000001; }
    void decreaseAcceration(){ acceleration-=0.000001; }

    void loadLevelEnemy();


    /**
     * 键盘
     * @param key
     * @param scancode
     * @param action  GLFW_RELEASE 松开 GLFW_PRESS 按下 GLFW_REPEAT 重复，一直按着
     * @param mods    GLFW_MOD_SHIFT 按下Shift键 GLFW_MOD_CONTROL 按下Ctrl键
     */
    void keyboard_event(int key, int action, int mods);

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


    //playerplane
    PlayerPlane* playerPlane;
};


#endif //EBATTLE_PLANE_GAME_SCENE_H
