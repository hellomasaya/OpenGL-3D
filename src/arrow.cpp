#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    static const GLfloat vertex_buffer_data[] = {
        -0.15f,-0.2f,-0.2f, // triangle 1 : begin
        -0.15f,-0.2f, 0.2f,
        -0.15f, 0.2f, 0.2f, // triangle 1 : end
        0.15f, 0.2f,-0.2f, // triangle 2 : begin
        -0.15f,-0.2f,-0.2f,
        -0.15f, 0.2f,-0.2f, // triangle 2 : end
        0.15f,-0.2f, 0.2f,
        -0.15f,-0.2f,-0.2f,
        0.15f,-0.2f,-0.2f,
        0.15f, 0.2f,-0.2f,
        0.15f,-0.2f,-0.2f,
        -0.15f,-0.2f,-0.2f,
        -0.15f,-0.2f,-0.2f,
        -0.15f, 0.2f, 0.2f,
        -0.15f, 0.2f,-0.2f,
        0.15f,-0.2f, 0.2f,
        -0.15f,-0.2f, 0.2f,
        -0.15f,-0.2f,-0.2f,
        -0.15f, 0.2f, 0.2f,
        -0.15f,-0.2f, 0.2f,
        0.15f,-0.2f, 0.2f,
        0.15f, 0.2f, 0.2f,
        0.15f,-0.2f,-0.2f,
        0.15f, 0.2f,-0.2f,
        0.15f,-0.2f,-0.2f,
        0.15f, 0.2f, 0.2f,
        0.15f,-0.2f, 0.2f,
        0.15f, 0.2f, 0.2f,
        0.15f, 0.2f,-0.2f,
        -0.15f, 0.2f,-0.2f,
        0.15f, 0.2f, 0.2f,
        -0.15f, 0.2f,-0.2f,
        -0.15f, 0.2f, 0.2f,
        0.15f, 0.2f, 0.2f,
        -0.15f, 0.2f, 0.2f,
        0.15f,-0.2f, 0.2f,

    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    static const GLfloat vertex_buffer_data1[] = {

        0.3f, -0.2f, 0.2f,
        0.3f, -0.2f, -0.2f,
        -0.3f, -0.2f, -0.2f,
        // -0.5f, 0.0f, 0.5f,

        -0.3f, -0.2f, 0.2f,
        -0.3f, -0.2f, -0.2f,
        0.3f, -0.2f, 0.2f,
        // -0.5f, 0.0f, 0.5f,

        0.0f, -0.8f, 0.0f,
        0.3f, -0.2f, 0.2f,
        0.3f, -0.2f, -0.2f,

        -0.3f, -0.2f, -0.2f,
        0.0f, -0.8f, 0.0f,
        0.3f, -0.2f, 0.2f,

        -0.3f, -0.2f, 0.2f,
        0.3f, -0.2f, 0.2f,
        0.0f, -0.8f, 0.0f,

        -0.3f, -0.2f, 0.2f,
        0.3f, -0.2f, 0.2f,
        0.0f, -0.8f, 0.0f,


    };

    this->object1 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data1, color, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
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

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

