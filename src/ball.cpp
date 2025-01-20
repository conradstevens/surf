#include <iostream>
#include <ostream>
#include "ball.h"
#include "shader.h"
#include "mesh.h"


// Where all the Ball data is stored:
const char* Ball::vertexShaderSource_static;
const char* Ball::fragmentShaderSource_static;
std::vector<float>* Ball::vertices_static;
std::vector<unsigned int>* Ball::index_buffer_static;
Shader Ball::shader_static;
Mesh Ball::mesh_static;

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
    // TODO Pass in vector pointers insted of dereferencing or find a way not to copy the vectors.
    mesh_static = Mesh(*vertices_static, shader_static, *index_buffer_static);
}

void Ball::unload() {
    delete vertices_static;
    delete index_buffer_static;
}

Ball::Ball(): Entity(&Ball::shader_static, &Ball::mesh_static) {}

