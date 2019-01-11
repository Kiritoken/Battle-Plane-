//
// Created by eli on 1/11/19.
//

#include <GL/glew.h>
#include "explosion_factory.h"
#include "explosion.h"
#include "../utilis/stb_image.h"

vector<uint > ExplosionFactory::texID;
vector<ExplosionInfo> ExplosionFactory::explosionArray;


void ExplosionFactory::loadExplosion() {
    std::string explosionImage="../res/image/blast_0_";
    unsigned int level=0;
    while(true) {
        ExplosionInfo explosionInfo;
        explosionInfo.texture_index=level;
        //最后一个是错误的纹理
        texID.push_back(explosionInfo.texture_index);
        glGenTextures(1, &texID[explosionInfo.texture_index]);
        //绑定纹理
        glBindTexture(GL_TEXTURE_2D, texID[explosionInfo.texture_index]);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载并生成纹理
        int i_width, i_height, nrChannels;
        string fileName=explosionImage+to_string(level)+".png";
        cout<<"正在载入Explosion： "<<fileName<<endl;
        unsigned char *data = stbi_load(fileName.c_str(), &i_width, &i_height, &nrChannels, 4);
        if (data) {
            //生成纹理
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, i_width, i_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Explosion资源加载完成" << std::endl;
            break;
        }
        stbi_image_free(data);


        explosionArray.push_back(explosionInfo);

        level++;
    }
}


shared_ptr<Explosion> ExplosionFactory::getExplosion(float _x, float _y, float _width, float _height, float _velocity,
                                                     float _acceleration, FLYING_DIRECTION _direction) {
    shared_ptr<Explosion> explosion(new Explosion(_x,_y,_width,_height,0));
    explosion->setVelocity(_velocity);
    explosion->setAcceleration(_acceleration);
    explosion->setDirection(_direction);
    return explosion;
}