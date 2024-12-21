#include <iostream>
#include <ostream>
#include "ball.h"
#include "shader.h"
#include "mesh.h"


Ball::Ball():
    vertexShaderSource(
        "#version 410 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
        "}\0"),
    fragmentShaderSource(
        "#version 410 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0"),
    vertices(
     {-0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f}
    ),
    index_buffer(
     {0, 1, 2,
        2, 3, 0}
    ),
    shader(initShader()),
    mesh(initMesh()) {}

Shader Ball::initShader() {
    return Shader(this->vertexShaderSource, this->fragmentShaderSource, 2);
}

Mesh Ball::initMesh() {
    return Mesh(this->vertices, this->shader, this->index_buffer);
}
