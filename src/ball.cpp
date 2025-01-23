#include "ball.h"


// Where all the Ball data is stored:
const char* Ball::vertexShaderSource_static;
const char* Ball::fragmentShaderSource_static;
std::vector<float>* Ball::vertices_static;
std::vector<unsigned int>* Ball::index_buffer_static;
std::vector<float>* Ball::x_splice;
std::vector<float>* Ball::y_splice;
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

    x_splice =  new std::vector<float>
        {1, 0, 1, 0, 1, 0, 1, 0};

    y_splice =  new std::vector<float>
        {0, 1, 0, 1, 0, 1, 0, 1};

    shader_static = Shader(vertexShaderSource_static, fragmentShaderSource_static, 2);
}

void Ball::unload() {
    delete vertices_static;
    delete index_buffer_static;
    delete x_splice;
    delete y_splice;
}

Ball::Ball(): Entity(&Ball::shader_static, vertices_static, index_buffer_static, x_splice, y_splice),
    direction({-1.0f, -2.0f}),
    speed(0.0001f) {
}

void Ball::step(long time) {
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
}


