#include "entity.h"


Entity::Entity(Shader* shader_, Mesh& mesh_):
    shader(shader_), mesh(mesh_), loc(Loc{}) {
}

Entity::Entity(Shader *shader_,
               std::vector<float>* vertices_,
               std::vector<unsigned int>* index_buffer_,
               Loc loc_) :
    shader(shader_),
    mesh(Mesh(vertices_, *shader, index_buffer_)),
    loc(loc_){
}

void Entity::move(float x, float y) {
    loc.x += x;
    loc.y += y;
    mesh.move(x, y);
}

void Entity::position(float x, float y) {
    float x_move = x - loc.x;
    float y_move = y - loc.y;
    loc.x = x;
    loc.y = y;
    mesh.move(x_move, y_move);
}

void Entity::scale(float s) {
    mesh.x_vec = s * mesh.x_vec_orig.array() + loc.x;
    mesh.y_vec = s * mesh.y_vec_orig.array() + loc.y;
}

void Entity::rotate(float angle) {
    // todo
    float c = cos(angle);
    float s = sin(angle);
}

bool Entity::isInBounds() {
    return loc.x - loc.x_buf > 1 || loc.x + loc.x_buf < -1 || loc.y - loc.y_buf > 1 || loc.y + loc.y_buf < -1;
}

