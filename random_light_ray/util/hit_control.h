#ifndef HIT_CONTROL_HPP
#define HIT_CONTROL_HPP

#include "constant.h"
#include "algorithm.h"



struct Material
{
    glm::vec3 Ambious;
    glm::vec3 Defuse;
    glm::vec3 Specular; 
    float shiny;

    glm::vec4 color;
    float smoothness;
    float transparency;
};

struct Light_source
{
    glm::vec3 coord;
    glm::vec3 Ambious;
    glm::vec3 Defuse;
    glm::vec3 Specular;
};

class hittable{
public:
    hittable() = default;

    virtual bool Hit_check(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, float* t, glm::vec4* ColorOut, Light_source light_source) const = 0 ;
    virtual glm::vec4 Color_handle(glm::vec3 ray, glm::vec3 P, float t, Light_source light_source) const = 0;
    virtual glm::vec3 get_normal(glm::vec3 P) const = 0;
    virtual Material get_material_info() const = 0;
    
    float hit;

};

class sphere : public hittable {
public:
    sphere() ;
    sphere(glm::vec3 Center, float radius, Material Light, float relative_environment):center(Center), R(radius), light_info(Light), relative(relative_environment) {};

    virtual glm::vec3 get_normal(glm::vec3 P)const override {
        return P - center;
    }

    virtual Material get_material_info() const override{
        return light_info;
    }

    virtual bool Hit_check(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, float* t, glm::vec4* ColorOut, Light_source light_source) const override {
        glm::vec3 cen_vec = center - P;
        float a = glm::dot(ray, ray);
        float b = (-2)*glm::dot(cen_vec, ray);
        float c = dot(cen_vec, cen_vec) - R*R;
        float denta = b*b - 4*a*c;
        if (denta >= 0){
            float t1 = (-b - sqrt(denta))/(2*a);
            float t2 = (-b + sqrt(denta))/(2*a);
            
            if ( t_min < t1 && t1 < t_max){*t = t1; *ColorOut = Color_handle(ray, P, t1, light_source); return true;}
            if ( t_min < t2 && t2 < t_max){*t = t2; *ColorOut = Color_handle(ray, P, t2, light_source); return true;}
        }
        return false;
    }

    virtual glm::vec4 Color_handle(glm::vec3 ray, glm::vec3 P, float t, Light_source light_source) const override{
        glm::vec3 Point_touch = P + ray*t;
        glm::vec3 light_vec = glm::normalize(light_source.coord - Point_touch);
        glm::vec3 normal = glm::normalize(get_normal(Point_touch));
        glm::vec3 vec_rand = random_vec();
        glm::vec3 normal_handled = glm::normalize(float(4)*normal + vec_rand);
        //std::cout<< normal_handled.x <<std::endl;
        glm::vec3 look_vec = glm::normalize(P - Point_touch);

        glm::vec3 ambious = light_info.Ambious * light_source.Ambious;

        float specular_figures = glm::dot(glm::normalize(glm::reflect(-light_vec, normal_handled)), look_vec);
        
        float defuse_figures = glm::dot(light_vec, normal_handled);
        if (defuse_figures < 0){defuse_figures = 0; specular_figures = 0;}
        glm::vec3 defuse = defuse_figures*light_info.Defuse*light_source.Defuse;

        if (specular_figures < 0){specular_figures = 0;}
        specular_figures = pow(specular_figures, light_info.shiny);
        glm::vec3 specular = specular_figures * light_info.Specular * light_source.Specular;
        
        glm::vec3 colorHandled = (ambious + defuse + specular) * glm::vec3(light_info.color);

        return glm::vec4(colorHandled, light_info.color.a);
    }

    glm::vec3 center;
    float R;
    float relative;
    Material light_info;
};

class surface : public hittable {
public:
    surface();
    surface(glm::vec3 Center, glm::vec3 normal_vec, Material Light) : C(Center), normal(normal_vec), light_info(Light) {};

    virtual glm::vec3 get_normal(glm::vec3 P)const override {
        return normal;
    }

    virtual Material get_material_info() const override{
        return light_info;
    }

    virtual bool Hit_check(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, float* t, glm::vec4* ColorOut, Light_source light_source)const override{
        if (glm::dot(ray, normal) == 0){return false;}
        float a = glm::dot(normal, (C - P));
        float b = glm::dot(ray, normal);
        float t_return = a/b;

        if (t_min < t_return && t_return < t_max) {
            *t = t_return; 
            glm::vec4 color_combine = Color_handle(ray, P, t_return, light_source); 
            *ColorOut = color_combine;
            return true;}

        return false;   
    }

    virtual glm::vec4 Color_handle(glm::vec3 ray, glm::vec3 P, float t, Light_source light_source) const override{
        glm::vec3 Point_touch = P + ray*t;
        glm::vec3 light_vec = glm::normalize(light_source.coord - Point_touch);
        glm::vec3 vec_rand = random_vec();
        glm::vec3 normal_handled = glm::normalize(float(2)*normal + vec_rand);
        glm::vec3 look_vec = glm::normalize(P - Point_touch);

        glm::vec3 ambious = light_info.Ambious * light_source.Ambious;

        float specular_figures = glm::dot(glm::reflect(-light_vec, normal_handled), look_vec);
        
        float defuse_figures = glm::dot(light_vec, normal_handled);
        if (defuse_figures < 0){defuse_figures = 0; specular_figures = 0;}
        glm::vec3 defuse = defuse_figures*light_info.Defuse*light_source.Defuse;
        
        if (specular_figures < 0){specular_figures = 0;}
        specular_figures = pow(specular_figures, light_info.shiny);
        glm::vec3 specular = specular_figures * light_info.Specular * light_source.Specular;
        
        glm::vec3 colorHandled = (ambious + defuse + specular) * glm::vec3(light_info.color);

        return glm::vec4(colorHandled, light_info.color.a);
    }

    glm::vec3 C, normal;

    Material light_info;
};

#endif