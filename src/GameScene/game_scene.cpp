//
// Created by eli on 1/8/19.
//
#define STB_IMAGE_IMPLEMENTATION
#include "../utilis/stb_image.h"
#include "game_scene.h"
#include <iostream>
#include <GL/glew.h>

GameScene::GameScene(int width,int height) {
    backgroundImage="../res/image/level1.jpg";
    this->width=width/2;
    this->height=height/2;

    velocity=0.001;
    acceleration=1;
    direction_flag= false;
    reset_uv();

    glGenTextures(1, &texture);
    //绑定纹理
    glBindTexture(GL_TEXTURE_2D, texture);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    int iwidth, iheight, nrChannels;
    unsigned char *data = stbi_load(backgroundImage.c_str(), &iwidth, &iheight, &nrChannels, 0);
    if (data){
        //生成纹理
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iwidth, iheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "背景图片加载失败" << std::endl;
    }
    stbi_image_free(data);
}

GameScene::~GameScene() {

}

void GameScene::render() {


    //启用纹理
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
  //  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


    glBegin(GL_QUADS);


    /**
     * UV 纹理坐标系，原点在坐上　ｘ轴向右　ｙ轴向下
     *
     */
    //左上
    glTexCoord2f(left_up.x, left_up.y); glVertex3f(-width,height,0.0f);
    //右上
    glTexCoord2f(right_up.x, right_up.y); glVertex3f(width, height, 0.0f);
    //右下
    glTexCoord2f(right_down.x, right_down.y); glVertex3f(width, -height, 0.0f);
    //左下
    glTexCoord2f(left_down.x, left_down.y); glVertex3f(-width, -height, 0.0f);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);

    update_uv();
}

void GameScene::update_uv() {
    if(right_down.x>1.0&&right_down.y>1.0){
      //  acceleration*=10;
        //std::cout<<"加速"<<std::endl;
        reset_uv();
        return;
    }
    if(right_down.y<1.0){
        left_up.y+=velocity*acceleration;
        right_up.y+=velocity*acceleration;
        right_down.y+=velocity*acceleration;
        left_down.y+=velocity*acceleration;
    }else{
        left_up.y=0;
        right_up.y=float(width)/10000;
        right_down.y=float(width)/10000;
        left_down.y=0;

        left_up.x+=velocity*acceleration;
        right_up.x+=velocity*acceleration;
        right_down.x+=velocity*acceleration;
        left_down.x+=velocity*acceleration;
    }
}

void GameScene::reset_uv() {
    left_up=glm::vec2(0.0,0.0);
    right_up=glm::vec2(float(width)/10000,0.0);
    right_down=glm::vec2(float(width)/10000,float(height)/10000);
    left_down=glm::vec2(0.0,float(height)/10000);
}