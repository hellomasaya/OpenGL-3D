#include "parachute.h"
#include "main.h"

Parachute::Parachute(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0;
    this->speed = 0.0;
    static const GLfloat vertex_buffer_data[] = {
        -0.1, 0.2, 0.1,
        -0.1, 0.2, -0.1,
        0.0, 0.4, 0.0,

        0.1, 0.2, 0.1,
        0.1, 0.2, -0.1,
        0.0, 0.4, 0.0,

        -0.1, 0.2, 0.1,
        0.1, 0.2, 0.1,
        0.0, 0.4, 0.0,

        -0.1, 0.2, -0.1,
        0.1, 0.2, -0.1,
        0.0, 0.4, 0.0,

         
    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_Para, GL_FILL);

    static const GLfloat vertex_buffer_data1[] = {
        -0.2f,-0.2f,-0.2f, // triangle 1 : begin
        -0.2f,-0.2f, 0.2f,
        -0.2f, 0.2f, 0.2f, // triangle 1 : end
        0.2f, 0.2f,-0.2f, // triangle 2 : begin
        -0.2f,-0.2f,-0.2f,
        -0.2f, 0.2f,-0.2f, // triangle 2 : end
        0.2f,-0.2f, 0.2f,
        -0.2f,-0.2f,-0.2f,
        0.2f,-0.2f,-0.2f,
        0.2f, 0.2f,-0.2f,
        0.2f,-0.2f,-0.2f,
        -0.2f,-0.2f,-0.2f,
        -0.2f,-0.2f,-0.2f,
        -0.2f, 0.2f, 0.2f,
        -0.2f, 0.2f,-0.2f,
        0.2f,-0.2f, 0.2f,
        -0.2f,-0.2f, 0.2f,
        -0.2f,-0.2f,-0.2f,
        -0.2f, 0.2f, 0.2f,
        -0.2f,-0.2f, 0.2f,
        0.2f,-0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f,-0.2f,-0.2f,
        0.2f, 0.2f,-0.2f,
        0.2f,-0.2f,-0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f,-0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f, 0.2f,-0.2f,
        -0.2f, 0.2f,-0.2f,
        0.2f, 0.2f, 0.2f,
        -0.2f, 0.2f,-0.2f,
        -0.2f, 0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        -0.2f, 0.2f, 0.2f,
        0.2f,-0.2f, 0.2f

    };

    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, COLOR_Para, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Parachute::tick() {
    this->rotation += 1;
    // this->position.x -= speed;
    this->position.y -= speed;
}

bounding_box_t Parachute::bounding_box() {
    double x = this->position.x, y = this->position.y, z = this->position.z;
    // The error in  z is due to the forward planks
    // Width and depth will also depend on the rotation 
    bounding_box_t bbox = { x, y, z, 0.4f, 0.6f, 0.4f };
    return bbox;
}