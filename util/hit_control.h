#ifndef HIT_CONTROL_HPP
#define HIT_CONTROL_HPP

#include "glm.hpp"

class hittable{
public:
    hittable() = default;

    virtual bool Hit_check(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, float* t) const = 0;

    float hit;
};

class sphere : public hittable {
public:
    sphere() ;
    sphere(glm::vec3 Center, float radius):center(Center), R(radius) {};

    virtual bool Hit_check(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, float* t) const override {
        glm::vec3 cen_vec = center - P;
        float a = glm::dot(ray, ray);
        float b = (-2)*glm::dot(cen_vec, ray);
        float c = dot(cen_vec, cen_vec) - R*R;
        float denta = b*b - 4*a*c;
        if (denta >= 0){
            float t1 = (-b - sqrt(denta))/(2*a);
            float t2 = (-b + sqrt(denta))/(2*a);
            
            if ( t_min <= t1 && t1 <= t_max){t = &t1; return true;}
            if ( t_min <= t2 && t2 <= t_max){t = &t2; return true;}
        }
        return false;
    }

    float hit;
    glm::vec3 center;
    float R;
};

#endif