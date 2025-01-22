#include "entity.h"


Entity::Entity(Shader* shader_, Mesh& mesh_):
    shader(shader_), mesh(mesh_) {
}

Entity::Entity(Shader* shader_,
    std::vector<float>* vertices_,
    std::vector<unsigned int>* index_buffer_,
    std::vector<float>* x_splice_,
    std::vector<float>* y_splice_) :
    shader(shader_),
    mesh(Mesh(vertices_, *shader, index_buffer_, x_splice_, y_splice_)){
}

void Entity::move(float x, float y) {
    mesh.move(x, y);
}

