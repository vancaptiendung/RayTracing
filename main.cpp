#include "color.h"

bool touch_sphere(glm::vec3 center, glm::vec3 ray_check, float radius, glm::vec3 P){
    glm::vec3 cen_vec = center - P;
    float a = glm::dot(ray_check, ray_check);
    float b = 2*glm::dot(cen_vec, ray_check);
    float c = dot(cen_vec, cen_vec) - radius*radius;
    return ((b*b - 4*a*c) >= 0);
}

int main() {

    // Image

    int image_width = 500;
    int image_height = 300;

    glm::vec3 camera = glm::vec3(image_width/2, image_height/2, 300);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            glm::vec3 ray = glm::vec3(i, j, 0) - camera;
            if (touch_sphere(glm::vec3(image_width/2, 100, -10), ray, 10, camera)){
                out_pixel(glm::vec3(100, 0, 0));}
            else{out_pixel(glm::vec3(0, 255, 130));}
        }
    }
}