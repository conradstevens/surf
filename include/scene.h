#ifndef SCENE_H
#define SCENE_H
#include "entity.h"
#include <chrono>
#include <thread>
#include <vector>

/**
 * @brief Abstract class of scene to render objects
 * Handles event loops
 * @note time steps are calculate in micro seconds as longs
 */
class Scene {
/**
 * @param time_last time that marks the start of the last event loop
 * @param time_now time that marks the start of the curent event loop
 * @param time_step time in microseconds that passed while the last event loup loaded (micro seconds)
 * @param fps_time_last time stamp used to calculate fps
 * @param frame_count used to calculate fps
 * @param fps frame rate
 * @param entities list of entities in the scene
 */

protected:
    std::chrono::steady_clock::time_point time_last, time_now;
    long time_step{};
    std::chrono::steady_clock::time_point fps_time_last;
    int frame_count{};

    /**
     * Iterate over scene entities and update their states according to the time passed and their kinematic properties
     * @param time_step
     */
    virtual void step(float time_step) = 0;

public:
    std::vector<Entity*> entities;
    float fps = {};

    Scene() = default;

    void addEntity(Entity* entity, float x, float y);
    void removeEntity(Entity* entity);

    void bindEntities();
    void reBindEntities();

    void startRender();
    void render();
};



#endif //SCENE_H
