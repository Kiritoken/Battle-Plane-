//
// Created by eli on 1/9/19.
//

#include <GL/glew.h>
#include <iostream>
#include "bullet_factory.h"
#include "../utilis/stb_image.h"

vector<BulletInfo> BulletFactory::bulletArray;
GLuint  BulletFactory::texID[100];

//TODO 读取json数据
void BulletFactory::loadBullet() {
    std::string bulletImage="../res/image/m";
    unsigned int level=1;
    while(true) {
        BulletInfo bulletInfo;
        bulletInfo._texture=texID+level-1;
        glGenTextures(1, bulletInfo._texture);
        //绑定纹理
        glBindTexture(GL_TEXTURE_2D, *bulletInfo._texture);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载并生成纹理
        int i_width, i_height, nrChannels;
        string fileName=bulletImage+to_string(level)+".png";
        cout<<"正在载入Bullet： "<<fileName<<endl;
        unsigned char *data = stbi_load(fileName.c_str(), &i_width, &i_height, &nrChannels, 4);
        if (data) {
            //生成纹理
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, i_width, i_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "子弹资源加载完成" << std::endl;
            break;
        }
        stbi_image_free(data);
        bulletInfo.attackPower=50.0f;
        bulletInfo.texturePath=fileName;
        bulletInfo.b_width=10;
        bulletInfo.b_height=20;

        bulletArray.push_back(bulletInfo);

        level++;
    }
}



Bullet* BulletFactory::getBullet(float _x, float _y,unsigned int level) {

    if(level>bulletArray.size())
        return nullptr;
    else {
        Bullet *bullet = new Bullet(_x, _y,bulletArray[level].b_width,bulletArray[level].b_height,bulletArray[level]._texture);

        //TODO json 数据　加速度　速度
        bullet->setVelocity(15.0f);
        bullet->setAcceleration(0.0f);
        return bullet;
    }
}