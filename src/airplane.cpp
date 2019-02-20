#include "airplane.h"
#include "main.h"

Airplane::Airplane(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0;
    this->roll = 0.0;
    this->xspeed = 0.05;
    xspeed = 1;
    yspeed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        -0.15f,-0.3f,-0.7f, // triangle 1 : begin
        -0.15f,-0.3f, 0.7f,
        -0.15f, 0.3f, 0.7f, // triangle 1 : end
        0.15f, 0.3f,-0.7f, // triangle 2 : begin
        -0.15f,-0.3f,-0.7f,
        -0.15f, 0.3f,-0.7f, // triangle 2 : end
        0.15f,-0.3f, 0.7f,
        -0.15f,-0.3f,-0.7f,
        0.15f,-0.3f,-0.7f,
        0.15f, 0.3f,-0.7f,
        0.15f,-0.3f,-0.7f,
        -0.15f,-0.3f,-0.7f,
        -0.15f,-0.3f,-0.7f,
        -0.15f, 0.3f, 0.7f,
        -0.15f, 0.3f,-0.7f,
        0.15f,-0.3f, 0.7f,
        -0.15f,-0.3f, 0.7f,
        -0.15f,-0.3f,-0.7f,
        -0.15f, 0.3f, 0.7f,
        -0.15f,-0.3f, 0.7f,
        0.15f,-0.3f, 0.7f,
        0.15f, 0.3f, 0.7f,
        0.15f,-0.3f,-0.7f,
        0.15f, 0.3f,-0.7f,
        0.15f,-0.3f,-0.7f,
        0.15f, 0.3f, 0.7f,
        0.15f,-0.3f, 0.7f,
        0.15f, 0.3f, 0.7f,
        0.15f, 0.3f,-0.7f,
        -0.15f, 0.3f,-0.7f,
        0.15f, 0.3f, 0.7f,
        -0.15f, 0.3f,-0.7f,
        -0.15f, 0.3f, 0.7f,
        0.15f, 0.3f, 0.7f,
        -0.15f, 0.3f, 0.7f,
        0.15f,-0.3f, 0.7f,

    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, COLOR_AIRPLANE2, GL_FILL);

    static const GLfloat vertex_buffer_data[] = {
        //rect-prism
        0.15f, 0.3f, -0.7f,
        -0.15f, 0.3f, -0.7f,
        0.0f, 0.0f, -1.2f,

        -0.15f, 0.3f, -0.7f,
        -0.15f, -0.3f, -0.7f,
        0.0f, 0.0f, -1.2f,
        
        0.15f, -0.3f, -0.7f,
        -0.15f, -0.3f, -0.7f,
        0.0f, 0.0f, -1.2f,

        0.15f, 0.3f, -0.7f,
        0.15f, -0.3f, -0.7f,
        0.0f, 0.0f, -1.2f,

        // //wings
        -0.15f, 0.3f, 0.0f,
        -0.4f, 0.0f, 0.7f,
        -0.15f, 0.3f, 0.7f,

        -0.15f, -0.3f, 0.0f,
        -0.4f, 0.0f, 0.7f,
        -0.15f, -0.3f, 0.7f,

        0.15f, 0.3f, 0.0f,
        0.4f, 0.0f, 0.7f,
        0.15f, 0.3f, 0.7f,

        0.15f, -0.3f, 0.0f,
        0.4f, 0.0f, 0.7f,
        0.15f, -0.3f, 0.7f,

        0.15f, 0.3f, 0.7f,
        0.15f, -0.3f, 0.7f,
        0.4f, 0.0f, 0.7f,

        0.4f, 0.0f, 0.7f,
        0.15f, 0.3f, 0.0f,
        0.15f, -0.3f, 0.0f,

        -0.15f, 0.3f, 0.7f,
        -0.15f, -0.3f, 0.7f,
        -0.4f, 0.0f, 0.7f,

        -0.4f, 0.0f, 0.7f,
        -0.15f, 0.3f, 0.0f,
        -0.15f, -0.3f, 0.0f,


    };

    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_AIRPLANE1, GL_FILL);
}

void Airplane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 360.0f), glm::vec3(0, 1, 0));
    glm::mat4 roll    = glm::rotate((float) (this->roll * M_PI / 360.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // roll          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate * roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Airplane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Airplane::tick() {
    // this->rotation += speed;
    this->position.z -= 0.05*cos(this->rotation * M_PI / 360.0f);
    this->position.x -= 0.05*sin(this->rotation * M_PI / 360.0f);
    // this->position.y -= speed;
}

bounding_box_t Airplane::bounding_box() {
    double x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x, y, z, 0.8f, 0.6f, 1.9f };
    return bbox;
}