//
// Created by eli on 1/9/19.
//

#include <GL/glew.h>
#include <iostream>
#include <random>
#include "bullet_factory.h"
#include "../utilis/stb_image.h"
#include "../object/bullet.h"
#include "../utilis/constant.h"
#include "../GameScene/game_object.h"

vector<BulletInfo> BulletFactory::bulletArray;
vector<GLuint>  BulletFactory::texID;

vector<BulletInfo> BulletFactory::enemyBulletArray;
vector<GLuint>  BulletFactory::enemyTexID;

//TODO 读取json数据
void BulletFactory::loadBullet() {
    std::string bulletImage="../res/image/m";
    unsigned int level=0;
    while(true) {
        BulletInfo bulletInfo;
        bulletInfo.texture_index=level;
        texID.push_back(bulletInfo.texture_index);
        glGenTextures(1, &texID[bulletInfo.texture_index]);
        //绑定纹理
        glBindTexture(GL_TEXTURE_2D, texID[bulletInfo.texture_index]);
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


    bulletImage="../res/image/em";
    level=0;
    while(true) {
        BulletInfo bulletInfo;
        bulletInfo.texture_index=level;
        enemyTexID.push_back(bulletInfo.texture_index);
        glGenTextures(1, &enemyTexID[bulletInfo.texture_index]);
        //绑定纹理
        glBindTexture(GL_TEXTURE_2D, enemyTexID[bulletInfo.texture_index]);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载并生成纹理
        int i_width, i_height, nrChannels;
        string fileName=bulletImage+to_string(level)+".png";
        cout<<"正在载入EnemyBullet： "<<fileName<<endl;
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

        enemyBulletArray.push_back(bulletInfo);

        level++;
    }
}



shared_ptr<Bullet> BulletFactory::getBullet(float _x, float _y,unsigned int level) {

    if(level>bulletArray.size())
        return nullptr;
    else {
        shared_ptr<Bullet> bullet(new Bullet(_x, _y,bulletArray[level].b_width,bulletArray[level].b_height,bulletArray[level].texture_index));
        //TODO json 数据　加速度　速度
        bullet->setVelocity(15.0f);
        bullet->setAcceleration(0.0f);
        return bullet;
    }
}


/**
 * 在x_min x_max之间随机产生子弹 y值相同
 * @param x_min
 * @param x_max
 * @param y
 */
void BulletFactory::genBulletsByPos(float x_min,float x_max,float _y,float _velocity,float _acceleration) {
    default_random_engine e(time(NULL));
    //解决首次运行只返回最大的问题
    uniform_int_distribution<int> u_init(0, 1);
    uniform_int_distribution<int> u_textureIndex(0, enemyTexID.size()-2);

    int gg=u_init(e);
    //随机纹理
    int Id=u_textureIndex(e);

    //随机获取正确的子弹数量 具体数量要更据飞机的宽度与子弹宽度确定
    float width=x_max-x_min;
    uniform_int_distribution<int> u_num(1, min(Constant::maxBulletsPerEnemy,int(width/enemyBulletArray[Id].b_width))); //随机数分布对象
    //随机数量
    int num=u_num(e);


    float _x=x_min;
    float interval=width/num;
    _x+=interval/2;
    for(int i=0;i<num;++i) {
        //位置
        shared_ptr<Bullet> bullet(new Bullet(_x, _y-enemyBulletArray[Id].b_height*0.5,enemyBulletArray[Id].b_width,enemyBulletArray[Id].b_height,
                                             enemyBulletArray[Id].texture_index));
        //下一位置
        _x+=interval;

        bullet->setAcceleration(_acceleration);
        bullet->setDirection(DOWN);
        bullet->setObjectType(ENEMY_BULLET);
        GameObject::flyingObjectSet.push_back(bullet);
    }
/*    cout<<"***********随机子弹**********************"<<endl;
    cout<<"子弹数量: "<<num<<endl;
    cout<<"子弹类型: "<<Id<<endl;
    cout<<"************************************"<<endl;
    cout<<endl;*/
}