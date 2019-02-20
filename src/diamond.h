#include "main.h"

#ifndef DIAMOND_H
#define DIAMOND_H


class Diamond {
public:
    Diamond() {}
    Diamond(float x, float y, float z, color_t color);
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
};

#endif // DIAMOND_H