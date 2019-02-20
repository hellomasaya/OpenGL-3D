#include "main.h"

#ifndef VOLACANO_H
#define VOLACANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    bounding_box_t bounding_box();

private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // VOLACANO_H