#include "compass.h"
#include "main.h"

Compass::Compass(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices  
    static const GLfloat vertex_buffer_data_box[] = {    
        -0.5f, 0.0f, 0.0f, // triangle 1 : begin
        0.5f, 0.0f, 0.0f,
        0.0f, 3.0f, 0.0f,// triangle 1 : end
        };

    this->object = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_box, COLOR_ARROW1, GL_FILL);

    GLfloat vertex_buffer_data[100000];
    int j=0;
    int angle = 0;
    double radius =3.0;
    for (int i=0; i<1080; i++) {
        if(i%3==0){
            vertex_buffer_data[j++] = 0.0f;
            vertex_buffer_data[j++] = 0.0f;
            vertex_buffer_data[j++] = 0.0f;
        } else if(i%3==1) {
            vertex_buffer_data[j++] = radius*cos((angle*3.1428)/180);
            vertex_buffer_data[j++] = radius*sin((angle*3.1428)/180);
            vertex_buffer_data[j++] = 0.0f;
            angle+=1;
        } else {
            vertex_buffer_data[j++] = radius*cos((angle*3.1428)/180);
            vertex_buffer_data[j++] = radius*sin((angle*3.1428)/180);
            vertex_buffer_data[j++] = 0.0f;
        }
    }

    this->object2 = create3DObject(GL_TRIANGLES, 10000, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 360.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object);
}

void Compass::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Compass::tick() {
    // this->rotation += speed;
    // this->position.z -= speed;
    // this->position.z -= 0.05*cos(this->rotation * M_PI / 360.0f);
    // this->position.x -= 0.05*sin(this->rotation * M_PI / 360.0f);
    // this->position.y -= speed;
}

