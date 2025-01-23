#ifndef ENTITY_H
#define ENTITY_H
#include "shader.h"
#include "mesh.h"
#include <vector>


class Entity {

public:
    Shader* shader = nullptr;
    Mesh mesh;

    // Constructors
    Entity(Shader* shader_, Mesh& mesh_);

    Entity(Shader* shader_,
        std::vector<float>* vertices_,
        std::vector<unsigned int>* index_buffer_,
        std::vector<float>* x_splice_,
        std::vector<float>* y_splice_);

    virtual ~Entity() = default;

    void move(float x, float y);
    virtual void step(long time) = 0;
};


#endif //ENTITY_H