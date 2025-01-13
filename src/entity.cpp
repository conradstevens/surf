#include "entity.h"
#include <iostream>


Entity::Entity(Shader shader, Mesh mesh):
    shader(std::move(shader)),
    mesh(std::move(mesh)) {
}

Entity::Entity(const char* vertexShaderSource_,
           const char* fragmentShaderSource_,
           std::vector<float> vertices_,
           std::vector<unsigned int> index_buffer_) :
    vertexShaderSource(vertexShaderSource_),
    fragmentShaderSource(fragmentShaderSource_),
    vertices(vertices_),
    index_buffer(index_buffer_),
    shader(initShader()),
    mesh(initMesh())
{}


Shader Entity::initShader(const char* vertexShaderSource, const char* fragmentShaderSource) {
    return Shader(vertexShaderSource, fragmentShaderSource, 2);
}

Shader Entity::initShader() {
    return Shader(this->vertexShaderSource, this->fragmentShaderSource, 2);
}

Mesh Entity::initMesh(std::vector<float> vertices, std::vector<unsigned int> index_buffer) {
    return Mesh(vertices, this->shader, index_buffer);
}

Mesh Entity::initMesh() {
    return Mesh(this->vertices, this->shader, this->index_buffer);
}