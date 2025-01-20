#include "scene.h"

Scene::Scene() :
    index_count(0) {
}

void Scene::addEntity(Entity entity){
    entities.push_back(entity);
    index_count += entity.mesh->index_buffer.size();
}

void Scene::bindEntities() {
    for (Entity entity : entities) {
        entity.mesh->bindToGPU();
    }
}

