#include "scene.h"

void Scene::addEntity(Entity* entity, float x, float y) {
    entity->setPosition(x, y);
    entity->mesh.bindToGPU();
    entities.push_back(entity);
}

void Scene::removeEntity(Entity* entity) {
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);
        delete entity;
    }
}

void Scene::bindEntities() {
    for (Entity* entity : entities) {
        entity->mesh.bindToGPU();
    }
}

void Scene::startRender() {
    time_last = std::chrono::high_resolution_clock::now();
    fps_time_last = std::chrono::high_resolution_clock::now();
    bindEntities();
}

void Scene::render() {
    frame_count ++;
    time_now = std::chrono::high_resolution_clock::now();
    time_step = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - time_last).count();

    step(time_step);

    for (Entity* entity : entities) {
        if (entity->isInBounds()) {
            removeEntity(entity);
        } else {
            entity->step(time_step);
            entity->mesh.reBindMeshToGPU();
            glDrawElements(GL_TRIANGLES, entity->mesh.index_buffer->size(), GL_UNSIGNED_INT, nullptr);
        }
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
