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
    bool ray_touch(glm::vec3 ray, glm::vec3 P, float t_min, float t_max){
        Hit_object.clear();
        bool Hit = false;
        float t_return;

        for (auto obj:Object){
            if (obj->Hit_check(ray, P, t_min, t_max, &t_return)){
                Hit_object.insert(Hit_object.end(), obj);
                Hit = true;
            }
        }
        return Hit;
    }
private:
    std::vector<hittable*> Object;
    std::vector<hittable*> Hit_object;
};

#endif