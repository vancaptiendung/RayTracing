#include "color.h"
#include "object_control.hpp"


float touch_sphere(glm::vec3 center, glm::vec3 ray_check, float radius, glm::vec3 P){
    glm::vec3 cen_vec = center - P;
    float a = glm::dot(ray_check, ray_check);
    float b = (-2)*glm::dot(cen_vec, ray_check);
    float c = dot(cen_vec, cen_vec) - radius*radius;
    float denta = b*b - 4*a*c;
    if (denta >= 0){
        float t1 = (-b - sqrt(denta))/(2*a);
        float t2 = (-b + sqrt(denta))/(2*a);
        return (t1 <= 0 ? t2 : t1);
    }
    return 0;
}

glm::vec3 sky(glm::vec2 coord){
    return glm::vec3(255-int(coord.y*255/1000),255-int(coord.y*255/800),255);
}

int main() {

    // Image

    int image_width = 1000;
    int image_height = 800;

    glm::vec3 camera = glm::vec3(image_width/2, image_height/2, 900);

    Lighting_parameter simple_light = {glm::vec3(0.01), glm::vec3(0.15), glm::vec3(0.5), 8};
    Light_source Light1 = {
        glm::vec3(10,10,10),
        glm::vec3(0.1), glm::vec3(0.5), glm::vec3(0.5)
    };

    //obj
    hittable* Sphere1 = new sphere(glm::vec3(image_width/2-100, image_height/2,70), 80, glm::vec4(1,1,0,1), simple_light);
    hittable* Sphere2 = new sphere(glm::vec3(image_width/2+100, image_height/2,50), 50, glm::vec4(0,1,0,1), simple_light);
    hittable* Surface1 = new surface(glm::vec3(0, image_height/2 - 30, 0), glm::vec3(0, -1, 0.5), glm::vec4(1), simple_light);
    hittable* Sun = new sphere(Light1.coord, 20, glm::vec4(1), simple_light);

    Objects Obj_ctr;
    Obj_ctr.add_object(Sphere1);
    Obj_ctr.add_object(Sphere2);
    Obj_ctr.add_object(Surface1);
    Obj_ctr.add_object(Sun);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            glm::vec3 ray = glm::vec3(i, j, 0) - camera ;
            // float touch = touch_sphere(glm::vec3(image_width/2, 50, 300), ray, 200, camera);
            // if (touch > 0){
            //     glm::vec3 color = handle_reflection_sphere(glm::vec3(image_width/2, 100, 300), touch * ray + camera);
            //     out_pixel(color);
            // }
            // else{out_pixel(sky(glm::vec2(i,j)));}
            glm::vec4 colorOut ;
            float touch = Obj_ctr.ray_touch(ray, camera, 0, 1, &colorOut, Light1);
            if (touch != NULL){
                glm::vec3 color_handled = glm::vec3(int(255*colorOut.x), int(255*colorOut.y), int(255*colorOut.z));
                out_pixel(color_handled);
            }
            else{out_pixel(sky(glm::vec2(i,j)));}
        }
    }
}