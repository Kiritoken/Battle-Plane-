//
// Created by eli on 1/10/19.
//

#include <iostream>
#include <GL/glew.h>
#include "enemy_factory.h"
#include "enemy_plane.h"
#include "../utilis/stb_image.h"
#include "../utilis/constant.h"
#include "../GameScene/game_object.h"
#include <random>
using namespace std;
using std::default_random_engine;
using std::uniform_int_distribution;

vector<EnemyInfo> EnemyFactory::enemyPlaneArray;
vector<unsigned int> EnemyFactory::texID;



void EnemyFactory::loadEnemyPlane() {
    std::string bulletImage="../res/image/enemy";
    unsigned int level=0;
    while(true) {
        EnemyInfo enemyInfo;
        enemyInfo.texture_index=level;
        //最后一个是错误的纹理
        texID.push_back(enemyInfo.texture_index);
        glGenTextures(1, &texID[enemyInfo.texture_index]);
        //绑定纹理
        glBindTexture(GL_TEXTURE_2D, texID[enemyInfo.texture_index]);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载并生成纹理
        int i_width, i_height, nrChannels;
        string fileName=bulletImage+to_string(level)+".png";
        cout<<"正在载入Enemy： "<<fileName<<endl;
        unsigned char *data = stbi_load(fileName.c_str(), &i_width, &i_height, &nrChannels, 4);
        if (data) {
            //生成纹理
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, i_width, i_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "敌机资源加载完成" << std::endl;
            break;
        }
        stbi_image_free(data);

        enemyInfo.attackPower=50.0f;
        enemyInfo.texturePath=fileName;
        enemyInfo.b_width=62;
        enemyInfo.b_height=62;

        enemyPlaneArray.push_back(enemyInfo);

        level++;
    }
}


shared_ptr<EnemyPlane> EnemyFactory::getEnemyPlane(float _x, float _y, unsigned int level) {
    if(level>enemyPlaneArray.size())
        return nullptr;
    else {
        shared_ptr<EnemyPlane> enemyPlane(new EnemyPlane(_x, _y,enemyPlaneArray[level].b_width,enemyPlaneArray[level].b_height,enemyPlaneArray[level].texture_index));
        //TODO json 数据　加速度　速度
        enemyPlane->setVelocity(10.0f);
        enemyPlane->setAcceleration(0.0f);
        enemyPlane->setDirection(DOWN);
        return enemyPlane;
    }
}


void EnemyFactory::genEnemyPlanes() {
    //TODO 读取关卡json数据

    default_random_engine e(time(NULL));
    uniform_int_distribution<int> u_num(0, 4); //随机数分布对象
    uniform_real_distribution<float> u_velocity(1, 2);
    uniform_real_distribution<float> u_acceleration(0, 0.05);
    uniform_int_distribution<int> u_textureIndex(0, texID.size()-2);
    //随机数量
    int num=u_num(e);
    for(int i=0;i<num;++i) {
        //随机速度
        float velocity=u_velocity(e);
        //随机加速度
        float acceleration=u_acceleration(e);
        //随机纹理
        int Id=u_textureIndex(e);
        //随机位置
        uniform_real_distribution<double> u_x(-Constant::screenWidth*0.5+enemyPlaneArray[Id].b_width*0.5,
                                            Constant::screenWidth*0.5-enemyPlaneArray[Id].b_width*0.5);
        auto _x=(float)u_x(e);
        auto _y=float((Constant::screenHeight+enemyPlaneArray[Id].b_height)*0.5);
        shared_ptr<EnemyPlane> enemyPlane(new EnemyPlane(_x, _y,enemyPlaneArray[Id].b_width,enemyPlaneArray[Id].
                                          b_height,enemyPlaneArray[Id].texture_index));

        enemyPlane->setVelocity(velocity);
        enemyPlane->setAcceleration(acceleration);
        enemyPlane->setDirection(DOWN);
        GameObject::enemySet.push_back(enemyPlane);

/*        cout<<"************************************"<<endl;
        cout<<"velocity: "<<velocity<<"  "<<"acceleration: "<<acceleration<<endl;
        cout<<_x<<" "<<_y<<endl;
        cout<<"************************************"<<endl;
        cout<<endl;*/
    }

}