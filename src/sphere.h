#include "main.h"

#ifndef SPHERE_H
#define SPHERE_H


class Sphere {
public:
    Sphere() {}
    Sphere(double x, double y,double z, color_t color);
    glm::vec3 position;
    double rotation;
    void draw(glm::mat4 VP);
    void set_position(double x, double y ,double z);
    bool tick();
    double speed;
    double yspeed;
    double radius;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SPHERE_H