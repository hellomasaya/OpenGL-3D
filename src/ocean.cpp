#include "ocean.h"
#include "main.h"

Ocean::Ocean(float x, float y, float z, color_t color) {
    static const GLfloat vertex_buffer_data[] = {
        -3000.0f,0.0f, 3000.0f,
        3000.0f, 0.0f, 3000.0f,
        3000.0f, 0.0f, -3000.0f,

        3000.0f, 0.0f, -3000.0f,
        -3000.0f,0.0f, -3000.0f,
        -3000.0f,0.0f, 3000.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_OCEAN, GL_FILL);
}

void Ocean::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ocean::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ocean::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

