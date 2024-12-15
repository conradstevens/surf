#include "ball.h"

#include <iostream>
#include <ostream>

#include "shader.h"
#include "mesh.h"


Ball::Ball(): shader(initShader()), mesh(initMesh()) {}

Shader Ball::initShader() {
    const char* vertexShaderSource = "#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
    "}\0";

    const char* fragmentShaderSource = "#version 410 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    return Shader(vertexShaderSource, fragmentShaderSource, 2);
}

Mesh Ball::initMesh() {
    std::vector<float> vertices = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f,  0.5f};
    return Mesh(vertices, shader);
}
