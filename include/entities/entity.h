#ifndef ENTITY_H
#define ENTITY_H
#include "../rendering//shader.h"
#include "../rendering/mesh.h"
#include "loc.h"
#include <vector>
#include <cmath>


/**
 * @brief Abstract class of entities that are rendered in a scene
 * @note Reused const elements are passed by reference
 * @note properties that are shared across entities of the same type are const static in their derived classes
 */
class Entity {
public:
     /**
      * @brief Static Const data members that are shared across derived entities of the same class. These values will be
      * defined in derived class's `init` function.
      * @param shader the objects shader
      * @param mesh the objects mesh
      */
    static constexpr size_t mesh_size = 0;
    static constexpr size_t buffer_size = 0;
    Mesh<mesh_size, buffer_size> mesh{};

    /**
      * @brief Getter for static data member method mesh_size
      * @return mesh size
      */
    static size_t getMeshSize() {return mesh_size;}

    /**
     * @brief Getter for static data member method buffer_size
     * @return buffer size
     */
    static size_t getBufferSize() {return buffer_size;}

    /**
      * @brief Getter for static data member method mesh_size
      * @return mesh size
      */
    virtual size_t getMeshSize_virtual() {return mesh_size;}

     /**
      * @brief Getter for static data member method buffer_size
      * @return buffer size
      */
     virtual size_t getBufferSize_virtual() {return buffer_size;}

    /**
     * @brief Data members all entities have
     * @param loc the objects location and kinematics
     */
    Loc loc{};

    /**
     * @bried Default constructor creates an empty Entity of default values
     * @note mesh and shader will not be defined
     */
    Entity() = default;
    virtual ~Entity() = default;

    /**
     * @brief TODO Set the position of an entity
     * @param x axis
     * @param y axis
     */
    void setPosition(float x, float y);

    /**
     * @brief TODO Set the scale of an entity
     * @param s scale
     */
    void setScale(float s);

    /**
     * @brief TODO Move the object relative to its current position
     * @param x axis
     * @param y axis
     */
    void move(float x, float y);

    /**
     * @brief TODO Set angle of entity
     * @param angle new angle
     */
    void setRotation(float angle);

    /**
     * @brief TODO Rotate the angle relative to its initial position
     * @param angle rotation amount
     */
    void rotate(float angle);

    /**
     * @brief TODO Return true if object is in the bounds
     * @return if is in boiunds
     */
    bool isInBounds();

    /**
     * @brief TODO What to do in a time step. Kinematics are applied to all entities
     * @param time
     */
    virtual void step(long time) = 0;
};


/**
 * @brief Template type concept requiring the type is derived from the Entity class
 */
template <typename T>
concept EntityDerived = std::derived_from<T, Entity>;

#endif //ENTITY_H