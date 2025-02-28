#ifndef SCENE_H
#define SCENE_H
#include <chrono>
#include <vector>
#include <thread>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "../entities/entity.h"
#include "../rendering/mesh_loader.h"


/**
 * @brief Scene that manages objects
 * @tparam EntityTypes List of entities that will be in scene
 */
template <EntityDerived... EntityTypes>
class Scene {
protected:
    /**
    * @brief Protected parameters for internal computation
    * @param time_last time that marks the start of the last event loop
    * @param time_now time that marks the start of the current event loop
    * @param time_step time in microseconds that passed while the last event loup loaded (micro seconds)
    * @param fps_time_last time stamp used to calculate fps
    * @param frame_count used to calculate fps
    * @param resources creates a map of object type to shader vertex pairs
    * @param entity_meshes a tuple containing all the meshes in the scene
    * @param entity_index the indices of the entities
    */
    std::chrono::steady_clock::time_point time_last{};
    std::chrono::steady_clock::time_point time_now{};
    long time_step{};
    std::chrono::steady_clock::time_point fps_time_last{};
    int frame_count{};
    // std::tuple<std::pair<EntityTypes, Mesh<EntityTypes::mesh_size, EntityTypes::buffer_size>>...>
    //     entity_meshes{std::make_pair(EntityTypes{}, EntityTypes::getResources())...};

    std::tuple<EntityTypes...> entity_meshes{EntityTypes{EntityTypes::getResources()}...};

    /**
     * @brief Return a reference to the type in the tuple.
     * @tparam Entity_T type whose mesh is being retrieved
     * @return reference to the type's mesh in the tuple
     */
    template <EntityDerived Entity_T>
    auto getMesh() -> Mesh<Entity_T::mesh_size, Entity_T::buffer_size>&;

    /**
    * Iterate over scene entities and update their states according to the time passed and their kinematic properties
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
     * TODO add rule of 3
     * @brief delete all the entities loaded to the screen
     */
    virtual ~Scene();

    /**
     * @brief Spawns a new object to the heap
     * @tparam Entity_T type of object to spawn
     */
    template <EntityDerived Entity_T>
    void spawn();

    /**
     * @brief Delete an entity from the list of entities
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


template <EntityDerived... EntityTypes>
template <EntityDerived Entity_T>
auto Scene<EntityTypes...>::getMesh() -> Mesh<Entity_T::mesh_size, Entity_T::buffer_size>& {
    using MeshType = Mesh<Entity_T::mesh_size, Entity_T::buffer_size>;
    MeshType& mesh = (std::get<Entity_T>(entity_meshes)).mesh;
    return mesh;
}

template <EntityDerived... EntityTypes>
Scene<EntityTypes...>::~Scene() {
    std::for_each(entities.begin(), entities.end(),
        [](Entity* entity) {delete entity;});
    entities.clear();
}

template <EntityDerived... EntityTypes>
template <EntityDerived Entity_T>
void Scene<EntityTypes...>::spawn() {
    using MeshType = Mesh<Entity_T::mesh_size, Entity_T::buffer_size>;
    MeshType& mesh = getMesh<Entity_T>();
    auto* entity = new Entity_T(mesh);
    entities.push_back(entity);
}

template <EntityDerived... EntityTypes>
void Scene<EntityTypes...>::deleteEntity(Entity* entity) {
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);
        delete entity;
    }
}

template <EntityDerived... EntityTypes>
void Scene<EntityTypes...>::render() {
    frame_count ++;
    time_now = std::chrono::high_resolution_clock::now();
    time_step = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - time_last).count();

    step(time_step);

    for (Entity* entity : entities) {
        entity->step(time_step);
        entity->mesh.reBindMeshToGPU();
        glDrawElements(GL_TRIANGLES, entity->getBufferSize_virtual(), GL_UNSIGNED_INT, nullptr);
    }
    time_last = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(0));

    // Calculate fps
    if (std::chrono::duration_cast<std::chrono::milliseconds>(time_now - fps_time_last).count() > 1000) {
        std::cout << "\rFPS: " << frame_count << std::flush;
        frame_count = 0;
        fps_time_last = std::chrono::high_resolution_clock::now();
    }
}

template <EntityDerived... EntityTypes>
void Scene<EntityTypes...>::start() {
    time_last = std::chrono::high_resolution_clock::now();
    fps_time_last = std::chrono::high_resolution_clock::now();
    for (Entity* entity : entities) {
        entity->mesh.bindToGPU();
    }
}


#endif //SCENE_H