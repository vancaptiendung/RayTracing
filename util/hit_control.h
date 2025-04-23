#ifndef HIT_CONTROL_HPP
#define HIT_CONTROL_HPP

#include "glm.hpp"

class hittable{
public:
    hittable() = default;

    virtual bool Hit_check(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, float* t, glm::vec4* ColorOut) const = 0;

    float hit;
};

class sphere : public hittable {
public:
    sphere() ;
    sphere(glm::vec3 Center, float radius, glm::vec4 Color):center(Center), R(radius), color(Color) {};

    virtual bool Hit_check(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, float* t, glm::vec4* ColorOut) const override {
        glm::vec3 cen_vec = center - P;
        float a = glm::dot(ray, ray);
        float b = (-2)*glm::dot(cen_vec, ray);
        float c = dot(cen_vec, cen_vec) - R*R;
        float denta = b*b - 4*a*c;
        if (denta >= 0){
            float t1 = (-b - sqrt(denta))/(2*a);
            float t2 = (-b + sqrt(denta))/(2*a);
            
            if ( t_min <= t1 && t1 <= t_max){*t = t1; *ColorOut = color; return true;}
            if ( t_min <= t2 && t2 <= t_max){*t = t2; *ColorOut = color; return true;}
        }
        return false;
    }

    glm::vec3 center;
    glm::vec4 color;
    float R;
};

class surface : public hittable {
public:
    surface();
    surface(glm::vec3 Center, glm::vec3 normal_vec, glm::vec4 Color) : C(Center), normal(normal_vec), color(Color) {};

    virtual bool Hit_check(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, float* t, glm::vec4* ColorOut)const override{
        if (glm::dot(ray, normal) == 0){return false;}
        float a = glm::dot(normal, (C - P));
        float b = glm::dot(ray, normal);
        float t_return = a/b;

        if (t_min < t_return && t_return < t_max) {*t = t_return; *ColorOut = color; return true;}
        return false;
    }

    glm::vec3 C, normal;
    glm::vec4 color;
};

#endif