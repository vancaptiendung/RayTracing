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
    float ray_touch(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, glm::vec4* color_output, Light_source source_light, glm::vec3* reflectVec, hittable* hit, hittable* ray_source){
        Hit_object.clear();
        bool Hit = false;
        float t_return = t_max;
        float t_touch = t_max;
        glm::vec4 colorReturn;

        for (auto obj:Object){
            if (obj == ray_source){continue;}
            if (obj->Hit_check(ray, P, t_min, t_max, &t_touch, &colorReturn, source_light)){
                Hit_object.insert(Hit_object.end(), obj);
                Hit = true;
                //std::cout<<t_touch<<std::endl;
                if (t_touch < t_return) {
                    t_return = t_touch;
                    *reflectVec = glm::reflect(ray, obj->get_normal(P + t_return*ray));
                    *color_output = colorReturn;
                    hit = obj;
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