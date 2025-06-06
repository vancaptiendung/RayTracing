#include "color.h"
#include "object_control.hpp"

int image_width = 1000;
int image_height = 800; 

glm::vec3 camera = glm::vec3(image_width/2, image_height/2, 900);

Material simple_light = {glm::vec3(0.1), glm::vec3(0.5), glm::vec3(0.8), 8,
                         glm::vec4(0.8,0.2,0.2, 0), 0, 0.5};
Light_source Light1 = {
    glm::vec3(image_width,image_height/2,500),
    glm::vec3(1), glm::vec3(1), glm::vec3(1)
};

//obj
Objects Obj_ctr;


glm::vec3 ray_ctr(glm::vec3 ray, glm::vec3 P, float* cout, hittable* Obj_touched){
    
    
    glm::vec4 colorOut ;
    glm::vec3 reflect_vec ;

    float touch = Obj_ctr.ray_touch(ray, P, 0.1, 5000/glm::length(ray), &colorOut, Light1, &reflect_vec, Obj_touched);
    if (touch != NULL && *cout < 2){
        //if (*cout == 1){std::cout<< "hit twice"<<std::endl;}
        hittable* Obj_touch = Obj_ctr.hit;
        * cout += 1;
        Material light_info = Obj_touch->get_material_info();
        // std::cout<< test.transparency << std::endl;
        return light_info.transparency * (ray_ctr(glm::normalize(reflect_vec), P + ray*touch, cout, Obj_touch)) + (1 - light_info.transparency)*glm::vec3(colorOut);
    }
    return glm::vec3(1);
}

glm::vec3 sky(glm::vec2 coord){
    return glm::vec3(255-int(coord.y*255/1000),255-int(coord.y*255/800),255);
}

int main(){
         
    hittable* Sphere1 = new sphere(glm::vec3(image_width/2, image_height/2 + 100,100), 100, simple_light, 1.5);
    hittable* Surface1 = new surface(glm::vec3(image_width/2, image_height,100), glm::vec3(0, -1, 0), simple_light);
    

    hittable* Sun = new sphere(Light1.coord, 20, simple_light, 1.5);

    Obj_ctr.add_object(Sphere1);
    //Obj_ctr.add_object(Sphere2);
    Obj_ctr.add_object(Surface1);
    
    
    //Obj_ctr.add_object(Sun);
        

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            glm::vec3 ray = (glm::vec3(i, j, 0) - camera) ;
            // float touch = touch_sphere(glm::vec3(image_width/2, 50, 300), ray, 200, camera);
            // if (touch > 0){
            //     glm::vec3 color = handle_reflection_sphere(glm::vec3(image_width/2, 100, 300), touch * ray + camera);
            //     out_pixel(color);
            // }
            // else{out_pixel(sky(glm::vec2(i,j)));}
            // glm::vec4 colorOut ;
            float cout = 0;
            glm::vec3 colorOut = ray_ctr(ray, camera, &cout, Sun);
            glm::vec3 colorHandled = glm::vec3(int(255 * colorOut.x),int(255 * colorOut.y),int(255 * colorOut.z));

            if (cout != 0){out_pixel(colorHandled);}

            
            else{out_pixel(sky(glm::vec2(i,j)));}
        }
    }
}