#ifndef SCENE_H
#define SCENE_H
#include "entity.h"
#include <chrono>
#include <thread>
#include <vector>

class Scene {

protected:
    std::chrono::steady_clock::time_point time_last;
    std::chrono::steady_clock::time_point time_now;
    long time_step{};  // micro second duration

    std::chrono::steady_clock::time_point fps_time_last;
    int frame_count{};

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
