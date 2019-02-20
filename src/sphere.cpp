#include "sphere.h"
#include "main.h"

const double twof = 2.0f;
const bool b = false;
const double onef = 1.0f;
const double zerof = 0.0f;
const long int one = 1;
const long int zero = 0;

Sphere::Sphere(double x, double y, double z, color_t color) {
    this->position = glm::vec3(x*onef, y*onef, z*onef);
    this->speed = zerof;
    this->yspeed = zerof;

    static const GLfloat vertex_buffer_data[] = {
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

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Sphere has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // GLfloat vertex_buffer_data[90000*one];
    // int sides = 100*one;
    // double angle = (2*M_PI)/double(sides);
    // int j=zero;
    // while(j<sides) {
    //     int i = zero;
    //     while (i < sides) {
    //         int k = sides*i + j*one;
    //         vertex_buffer_data[9*k*one] = zerof;
    //         vertex_buffer_data[9*k + one] = zerof;  
    //         vertex_buffer_data[9*k + 2*one] = radius*sin(j*angle);
    //         vertex_buffer_data[9*k + 3*one] = radius*cos(i*angle)*cos(j*angle); 
    //         vertex_buffer_data[9*k + 4*one] = radius*sin(i*angle)*cos(j*angle);
    //         vertex_buffer_data[9*k + 5*one] = radius*sin(j*angle); 
    //         vertex_buffer_data[9*k + 6*one] = radius*cos((i+1)*angle)*cos(j*angle); 
    //         vertex_buffer_data[9*k + 7*one] = radius*sin((i+1)*angle)*cos(j*angle); 
    //         vertex_buffer_data[9*k + 8*one] = radius*sin(j*angle); 
    //         i++;
    //     }
    //     this->object = create3DObject(GL_TRIANGLES, sides*sides*3, vertex_buffer_data, color, GL_FILL);
    //     j++;
    // }   
}

void Sphere::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(onef);
    // Rotate about y axis and not center of object
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(one, zero, zero));
    // No need as coords centered at 0, 0, 0 of Sphere arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[zero][zero]);
    draw3DObject(this->object);
}

void Sphere::set_position(double x, double y,double z) {
    this->position = glm::vec3(x, y, z);
}

bool Sphere::tick() {
    this->position.y += yspeed*onef;
    this->yspeed -= 4*onef/1000.0;
    this->position.z -= speed*cos(rotation*M_PI/180.0f*onef);   
    this->position.x += speed*sin(rotation*M_PI/180.0f*onef); 
    return this->position.y < -12.0f*onef;
}

bounding_box_t Sphere::bounding_box() {
    double x = this->position.x*onef, y = this->position.y*onef, z = this->position.z*onef;
    bounding_box_t bbox = { x*onef, y*onef,z*onef, 0.4, 0.4, 0.4};
    return bbox;
}

