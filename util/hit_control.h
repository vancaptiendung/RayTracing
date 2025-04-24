#ifndef HIT_CONTROL_HPP
#define HIT_CONTROL_HPP

#include "glm.hpp"

struct Lighting_parameter
{
    glm::vec3 Ambious;
    glm::vec3 Defuse;
    glm::vec3 Specular; 
    float shiny;
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
    float hit;
};

class sphere : public hittable {
public:
    sphere() ;
    sphere(glm::vec3 Center, float radius, glm::vec4 Color, Lighting_parameter Light):center(Center), R(radius), color(Color), light(Light) {};

    virtual bool Hit_check(glm::vec3 ray, glm::vec3 P, float t_min, float t_max, float* t, glm::vec4* ColorOut, Light_source light_source) const override {
        glm::vec3 cen_vec = center - P;
        float a = glm::dot(ray, ray);
        float b = (-2)*glm::dot(cen_vec, ray);
        float c = dot(cen_vec, cen_vec) - R*R;
        float denta = b*b - 4*a*c;
        if (denta >= 0){
            float t1 = (-b - sqrt(denta))/(2*a);
            float t2 = (-b + sqrt(denta))/(2*a);
            
            if ( t_min <= t1 && t1 <= t_max){*t = t1; *ColorOut = Color_handle(ray, P, t1, light_source); return true;}
            if ( t_min <= t2 && t2 <= t_max){*t = t2; *ColorOut = Color_handle(ray, P, t2, light_source); return true;}
        }
        return false;
    }

    virtual glm::vec4 Color_handle(glm::vec3 ray, glm::vec3 P, float t, Light_source light_source) const override{
        glm::vec3 Point_touch = ray + P*t;
        glm::vec3 light_vec = glm::normalize(light_source.coord - Point_touch);
        glm::vec3 normal_handled = glm::normalize(Point_touch - center);
        glm::vec3 look_vec = glm::normalize(P - Point_touch);

        glm::vec3 ambious = light.Ambious * glm::vec3(color);
        
        float defuse_figures = glm::dot(light_vec, normal_handled);
        if (defuse_figures < 0){defuse_figures = 0;}
        glm::vec3 defuse = defuse_figures*glm::vec3(color);

        float specular_figures = glm::dot(normal_handled, glm::normalize(light_vec + look_vec));
        if (specular_figures < 0){specular_figures = 0;}
        specular_figures = pow(specular_figures, light.shiny);
        glm::vec3 specular = specular_figures * light.Specular * glm::vec3(color);
        
        glm::vec3 colorHandled = ambious + defuse + specular;

        return glm::vec4(colorHandled, color.a);
    }

    glm::vec3 center;
    glm::vec4 color;
    float R;
    Lighting_parameter light;
};

class surface : public hittable {
public:
    surface();
    surface(glm::vec3 Center, glm::vec3 normal_vec, glm::vec4 Color, Lighting_parameter Light) : C(Center), normal(normal_vec), color(Color), light(Light) {};

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
        glm::vec3 Point_touch = ray + P*t;
        glm::vec3 light_vec = glm::normalize(light_source.coord - Point_touch);
        glm::vec3 normal_handled = glm::normalize(normal);
        glm::vec3 look_vec = glm::normalize(P - Point_touch);

        glm::vec3 ambious = light.Ambious * glm::vec3(color);
        
        float defuse_figures = glm::dot(light_vec, normal_handled);
        if (defuse_figures < 0){defuse_figures = 0;}
        glm::vec3 defuse = defuse_figures*glm::vec3(color);

        float specular_figures = glm::dot(normal_handled, glm::normalize(light_vec + look_vec));
        if (specular_figures < 0){specular_figures = 0;}
        specular_figures = pow(specular_figures, light.shiny);
        glm::vec3 specular = specular_figures * light.Specular * glm::vec3(color);
        
        glm::vec3 colorHandled = ambious + defuse + specular;

        return glm::vec4(colorHandled, color.a);
    }

    glm::vec3 C, normal;
    glm::vec4 color;

    Lighting_parameter light;
};

#endif