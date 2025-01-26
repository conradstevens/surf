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
    mesh.x_vec_scaled = s * mesh.x_vec_orig;
    mesh.y_vec_scaled = s * mesh.y_vec_orig;

    mesh.x_vec.array() = mesh.x_vec_scaled.array() + loc.x;
    mesh.y_vec.array() = mesh.y_vec_scaled.array() + loc.y;
}

void Entity::rotate(float angle) {
    float c = cos(angle);
    float s = sin(angle);

    mesh.x_vec = c * mesh.x_vec_scaled - s * mesh.y_vec_scaled;
    mesh.y_vec = s * mesh.x_vec_scaled + c * mesh.y_vec_scaled;

    mesh.x_vec.array() = mesh.x_vec.array() + loc.x;
    mesh.y_vec.array() = mesh.y_vec.array() + loc.y;
}

bool Entity::isInBounds() {
    return loc.x - loc.x_buf > 1 || loc.x + loc.x_buf < -1 || loc.y - loc.y_buf > 1 || loc.y + loc.y_buf < -1;
}

