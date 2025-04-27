#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include "glm.hpp"

void out_pixel(glm::vec3 color){
    std::cout<< color.x<<" "<<color.y<<" "<<color.z<<std::endl;
}

#endif