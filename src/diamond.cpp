#include "diamond.h"
#include "main.h"

Diamond::Diamond(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0;
    static const GLfloat vertex_buffer_data[] = {
        -0.1, 0.0, 0.1,
        -0.1, 0.0, -0.1,
        0.0, 0.3, 0.0,

        0.1, 0.0, 0.1,
        0.1, 0.0, -0.1,
        0.0, 0.3, 0.0,

        -0.1, 0.0, 0.1,
        0.1, 0.0, 0.1,
        0.0, -0.3, 0.0,

        -0.1, 0.0, -0.1,
        0.1, 0.0, -0.1,
        0.0, -0.3, 0.0,
         
    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_FEULUP1, GL_FILL);

    static const GLfloat vertex_buffer_data1[] = {

        -0.1, 0.0, 0.1,
        0.1, 0.0, 0.1,
        0.0, 0.3, 0.0,

        -0.1, 0.0, -0.1,
        0.1, 0.0, -0.1,
        0.0, 0.3, 0.0,

        -0.1, 0.0, 0.1,
        -0.1, 0.0, -0.1,
        0.0, -0.3, 0.0,

        0.1, 0.0, 0.1,
        0.1, 0.0, -0.1,
        0.0, -0.3, 0.0,

    };

    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data1, COLOR_FEULUP2, GL_FILL);
}

void Diamond::draw(glm::mat4 VP) {
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

void Diamond::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Diamond::tick() {
    this->rotation += 1;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Diamond::bounding_box() {
    double x = this->position.x, y = this->position.y, z = this->position.z;
    // The error in  z is due to the forward planks
    // Width and depth will also depend on the rotation 
    bounding_box_t bbox = { x, y, z, 0.2f, 0.6f, 0.2f };
    return bbox;
}