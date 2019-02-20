#include "main.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane {
public:
    Airplane() {}
    Airplane(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float roll;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xspeed;
    double yspeed;
    bounding_box_t bounding_box();

private:
    VAO *object;
    VAO *object2;
};

#endif // AIRPLANE_H