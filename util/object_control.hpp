#ifndef OBJECT_CONTROL_HPP
#define OBJECT_CONTROL_HPP

#include "hit_control.h"
#include <iostream>
#include <vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class Objects{
public:

    void add_object(hittable* Obj){Object.insert(Object.end(), Obj);}
    float ray_touch(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, glm::vec4* color_output, Light_source source_light){
        Hit_object.clear();
        bool Hit = false;
        float t_return = t_max;
        float t_touch = t_max;
        glm::vec4 colorReturn;

        for (auto obj:Object){
            if (obj->Hit_check(ray, P, t_min, t_max, &t_touch, &colorReturn, source_light)){
                Hit_object.insert(Hit_object.end(), obj);
                Hit = true;
                //std::cout<<t_touch<<std::endl;
                if (t_touch < t_return) {
                    t_return = t_touch;
                    *color_output = colorReturn;
                }
            }
        }
        return Hit ? t_return : NULL;
    }
private:
    std::vector<hittable*> Object;
    std::vector<hittable*> Hit_object;
};

#endif