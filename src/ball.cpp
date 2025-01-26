#include "ball.h"


// Where static Ball data is stored:
const char* Ball::vertexShaderSource_static;
const char* Ball::fragmentShaderSource_static;
std::vector<float>* Ball::vertices_static;
std::vector<unsigned int>* Ball::index_buffer_static;
Shader Ball::shader_static;

void Ball::load() {
    vertexShaderSource_static =
        "#version 410 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
        "}\0";

    fragmentShaderSource_static =
        "#version 410 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.0f, 0.5f, 1.0f, 1.0f);\n"
        "}\0";

    vertices_static =  new std::vector<float>
        {-0.05f, -0.05f,
         0.05f, -0.05f,
         0.05f,  0.05f,
        -0.05f,  0.05f};

    index_buffer_static = new std::vector<unsigned int>
        {0, 1, 2,
         2, 3, 0};

    shader_static = Shader(vertexShaderSource_static, fragmentShaderSource_static, 2);
}

void Ball::unload() {
    delete vertices_static;
    delete index_buffer_static;
}

Ball::Ball(): Entity(&Ball::shader_static, vertices_static, index_buffer_static,
        Loc{0.0f, 0.0f, 0.071f, 0.071f}),
    direction({-1.0f, -2.0f}),
    speed(0.0005f),
    rpm(1.0f){
}

Ball::Ball(float scale_, std::vector<float> direction_, float speed_, float rpm_):
    Entity(&Ball::shader_static, vertices_static, index_buffer_static,
        Loc{0.0f, 0.0f, 0.071f * 2, 0.071f * 2}),
    scale(scale_),
    direction(std::move(direction_)),
    speed(speed_),
    rpm(rpm_){
    setScale(scale);
}

void Ball::step(long time) {
    // Move
    float move_increment = time * speed;
    float angle = atan(direction[1] / direction[0]);
    float x_increment = move_increment * cos(angle);
    float y_increment = move_increment * sin(angle);

    x_increment = fabs(x_increment);
    y_increment = fabs(y_increment);

    if (direction[0] < 0.0f) {
        x_increment = -x_increment;
    } if (direction[1] < 0.0f) {
        y_increment = -y_increment;
    }

    move(x_increment, y_increment);

    // Rotate
    float rotation_step = rpm * time / 1000 * 2 * 3.14159265f;
    loc.angle += rotation_step;
    rotate(loc.angle);
}


