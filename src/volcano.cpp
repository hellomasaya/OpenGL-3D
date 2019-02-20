#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    static const GLfloat vertex_buffer_data[] = {

        -0.5f, 0.0f, 1.0f,
        -0.5f, 0.0f, -1.0f,
        0.0f, 4.0f, 0.0f,

        0.5f, 0.0f, 1.0f,
        0.5f, 0.0f, -1.0f,
        0.0f, 4.0f, 0.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_VOLCANO, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {

        -0.5f, 0.0f, -1.0f,
        0.5f, 0.0f, -1.0f,
        0.0f, 4.0f, 0.0f,

        -0.5f, 0.0f, 1.0f,
        0.5f, 0.0f, 1.0f,
        0.0f, 4.0f, 0.0f,

    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_VOLCANO2, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Volcano::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Volcano::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Volcano::bounding_box() {
    double x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x, y, z, 2.0f, 20.0f, 4.0f };
    return bbox;
}