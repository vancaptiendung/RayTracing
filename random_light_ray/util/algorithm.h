#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "constant.h"


glm::vec3 random_vec(){
    glm::vec3 vec_rand;
    for (int k = 0; k < 3; k++){
        
        float number_random = std::rand()%101;
        vec_rand[k] = number_random;
        //std::cout<< number_random;
    }
    //std::cout<<std::endl;

    return glm::normalize(vec_rand);
}

float focal_length(float relative_environment, float R1, float R2){
    float focal = 1/((relative_environment - 1)*(1/R1 + 1/R2));
    return focal;
}


#endif