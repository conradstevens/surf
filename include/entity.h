#ifndef ENTITY_H
#define ENTITY_H
#include "shader.h"
#include "mesh.h"
#include <memory>


class Entity {

public:
    Shader* shader = nullptr;
    Mesh* mesh = nullptr;;

    // Constructors
    Entity(Shader* shader_, Mesh* mesh_);
};


#endif //ENTITY_H