//
// Created by eli on 1/9/19.
//

#include <iostream>
#include "flying_object.h"

FlyingObject::~FlyingObject() {
    std::cout<<"基类被析构"<<std::endl;
    //delete texture;
}
