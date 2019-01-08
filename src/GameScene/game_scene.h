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

    //判断是否向下遍历
    bool direction_flag;

    void reset_uv();
    void update_uv();
};


#endif //EBATTLE_PLANE_GAME_SCENE_H
