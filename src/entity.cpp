#include "entity.h"


Entity::Entity(Shader* shader_, Mesh& mesh_):
    shader(shader_), mesh(mesh_), loc(Loc{}) {
}

Entity::Entity(Shader* shader_,
    std::vector<float>* vertices_,
    std::vector<unsigned int>* index_buffer_,
    std::vector<float>* x_splice_,
    std::vector<float>* y_splice_) :
    shader(shader_),
    mesh(Mesh(vertices_, *shader, index_buffer_, x_splice_, y_splice_)),
    loc(Loc{}){
}

Entity::Entity(Shader* shader_,
    std::vector<float>* vertices_,
    std::vector<unsigned int>* index_buffer_,
    std::vector<float>* x_splice_,
    std::vector<float>* y_splice_,
    Loc loc_) :
    shader(shader_),
    mesh(Mesh(vertices_, *shader, index_buffer_, x_splice_, y_splice_)),
    loc(loc_){
}

void Entity::move(float x, float y) {
    loc.x += x;
    loc.y += y;
    mesh.move(x, y);
}

void Entity::position(float x, float y) {
    loc.x = x;
    loc.y = y;
    mesh.position(x, y);
}

void Entity::scale(float s) {
    mesh.render_vertices = Eigen::Map<Eigen::VectorXf>(mesh.vertices->data(), mesh.vertices->size());
    mesh.render_vertices = mesh.render_vertices * s;
    mesh.position(loc.x, loc.y);
    loc.x = loc.x * s;  // May require tweaking for long objs
    loc.y = loc.y * s;
}

void Entity::rotate(float angle) {
    float c = cos(angle);
    float s = sin(angle);


}

bool Entity::isInBounds() {
    return loc.x - loc.x_buf > 1 || loc.x + loc.x_buf < -1 || loc.y - loc.y_buf > 1 || loc.y + loc.y_buf < -1;
}

