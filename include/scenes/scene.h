#ifndef SCENE_H
#define SCENE_H
#include <chrono>
#include <thread>
#include <vector>
#include <functional>
#include <unordered_map>
#include <typeindex>

#include "../entities/entity.h"
#include "../rendering/mesh.h"
#include "../rendering/mesh_loader.h"


class Scene {

protected:

    // TODO EntityMeshes entity_meshes{};

    /**
    * @brief Protected parameters for internal computation
    * @param time_last time that marks the start of the last event loop
    * @param time_now time that marks the start of the current event loop
    * @param time_step time in microseconds that passed while the last event loup loaded (micro seconds)
    * @param fps_time_last time stamp used to calculate fps
    * @param frame_count used to calculate fps
    * @param resources creates a map of object type to shader vertex pairs
    */

    std::chrono::steady_clock::time_point time_last{};
    std::chrono::steady_clock::time_point time_now{};
    long time_step{};
    std::chrono::steady_clock::time_point fps_time_last{};
    int frame_count{};
    MeshLoader mesh_loader{};

    /**
    * Iterate over scene entities and update their states according to the time passed and their kinematic properties
    * TODO
    * @param time_step
    */
    virtual void step(long time_step){}

    public:
    /**
    * @brief Publicly available data members
    * @param fps frame rate
    * @param entities list of entity pointers in the scene
    */
    float fps = {};
    std::vector<Entity*> entities;

    /**
    * @brief Loads all the entities in the scene
    * @note Each scene will load its own set of entities and potentially spawn them
    */
    Scene() = default;

    /**
    * @brief delete all the entities loaded to the screen
    */
    virtual ~Scene();

    /**
    * @brief Spawns a new object to the heap
    * TODO Optimize
    * @param entityType type of object to spawn
    */
    template <EntityDerived Entity_T>
    void spawn();

    /**
    * @brief Delete an entity from the list of entities
    * TODO Optimize
    * @param entity
    */
    void deleteEntity(Entity* entity);

    /**
     * @brief Initializes the rendering process given the entities in entities
     */
    void render();

    /**
     * @brief Stars rendering the scene
     */
    void start();

    // void render();
};



#endif //SCENE_H
