#include "pool.h"
#include "main.h"
Pool::Pool(float x, float z, color_t color) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->angular_speed = 0.5;
    this->level_angle = 0;
    speed = 0.2;
    static const GLfloat vertex_buffer_data[] = {
        -12345,-12345,-12345,
        -12345,-12345, 12345,
        -12345, 12345, 12345,
        12345, 12345,-12345,
        -12345,-12345,-12345,
        -12345, 12345,-12345,
        12345,-12345, 12345,
        -12345,-12345,-12345,
        12345,-12345,-12345,
        12345, 12345,-12345,
        12345,-12345,-12345,
        -12345,-12345,-12345,
        -12345,-12345,-12345,
        -12345, 12345, 12345,
        -12345, 12345,-12345,
        12345,-12345, 12345,
        -12345,-12345, 12345,
        -12345,-12345,-12345,
        -12345, 12345, 12345,
        -12345,-12345, 12345,
        12345,-12345, 12345,
        12345, 12345, 12345,
        12345,-12345,-12345,
        12345, 12345,-12345,
        12345,-12345,-12345,
        12345, 12345, 12345,
        12345,-12345, 12345,
        12345, 12345, 12345,
        12345, 12345,-12345,
        -12345, 12345,-12345,
        12345, 12345, 12345,
        -12345, 12345,-12345,
        -12345, 12345, 12345,
        12345, 12345, 12345,
        -12345, 12345, 12345,
        12345,-12345, 12345
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Pool::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    glm::mat4 rotate2   = glm::rotate((float) (this->level_angle * M_PI / 180.0f), glm::vec3(
                                          this->position.x,
                                          this->position.z,
                                          this->position.y));
    Matrices.model *= (translate * rotate * rotate2);
    glm::mat4 MVP = VP * Matrices.model;
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     glUniform1f(Matrices.Transparency, 0.75);
    draw3DObject(this->object);
     glDisable(GL_BLEND);
}

void Pool::set_position(float x, float z) {
    this->position = glm::vec3(x, 0, z);
}

void Pool::shm(){
    if(level_angle < -10.0f || level_angle > 10.0f){
        angular_speed = -angular_speed;
    }
    this->level_angle += angular_speed;
}

void Pool::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
