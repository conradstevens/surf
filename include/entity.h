#ifndef ENTITY_H
#define ENTITY_H
#include "shader.h"
#include "mesh.h"
#include "loc.h"
#include <vector>
#include <cmath>

/**
 * @brief Abstract class of entities that are rendered in a scene
 * @note Reused const elements are passed by reference
 * @note properties that are shared across entities of the same type are const static in their derived classes
 */
class Entity {
    /**
     * @param shader the objects shader
     * @param mesh the objects mesh
     * @param loc the objects location and kinematics
     */
public:
    Shader* shader{};
    Mesh mesh{};
    Loc loc{};

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