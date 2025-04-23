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

glm::vec3 handle_reflection_sphere(glm::vec3 center, glm::vec3 touch_point){
    int z = touch_point.z; 
    return glm::vec3(z);
}

glm::vec3 sky(glm::vec2 coord){
    return glm::vec3(255-int(coord.y*255/1000),255-int(coord.y*255/800),255);
}

int main() {

    // Image

    int image_width = 1000;
    int image_height = 800;

    glm::vec3 camera = glm::vec3(image_width/2, image_height/2, 900);

    //obj
    hittable* Sphere1 = new sphere(glm::vec3(image_width/2-100, image_height/2,70), 80, glm::vec4(255,255,0,255));
    hittable* Sphere2 = new sphere(glm::vec3(image_width/2+100, image_height/2,50), 50, glm::vec4(0,255,0,255));
    hittable* Surface1 = new surface(glm::vec3(0, image_height/2 + 50, 0), glm::vec3(0, 1, 0), glm::vec4(0,0,255,255));

    Objects Obj_ctr;
    Obj_ctr.add_object(Sphere1);
    Obj_ctr.add_object(Sphere2);
    Obj_ctr.add_object(Surface1);

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
            float touch = Obj_ctr.ray_touch(ray, camera, 0, 1, &colorOut);
            if (touch != NULL){
                glm::vec3 color_handled = glm::vec3(colorOut.x, colorOut.y, colorOut.z);
                out_pixel(color_handled);
            }
            else{out_pixel(sky(glm::vec2(i,j)));}
        }
    }
}