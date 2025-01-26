#ifndef ENTITY_H
#define ENTITY_H
#include "shader.h"
#include "mesh.h"
#include <vector>
#include <cmath>


struct Loc {
    float x{}, y{};
    float x_buf{}, y_buf{};
    float angle{};

    Loc() = default;
    Loc(float x, float y) : x{x}, y{y} {}
    Loc(float x, float y, float x_buf, float y_buf) : x{x}, y{y}, x_buf{x_buf}, y_buf{y_buf} {}
};

class Entity {

public:
    Shader* shader{};
    Mesh mesh;
    Loc loc;

    Entity(Shader* shader_, Mesh& mesh_);

    Entity(Shader *shader_,
           std::vector<float>* vertices_,
           std::vector<unsigned int>* index_buffer_,
           Loc loc_);

    virtual ~Entity() = default;

    void setPosition(float x, float y);
    void setScale(float s);
    void move(float x, float y);
    void rotate(float angle);
    bool isInBounds();

    virtual void step(long time) = 0;
};


#endif //ENTITY_H