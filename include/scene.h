#ifndef SCENE_H
#define SCENE_H
#include "entity.h"
#include <vector>

class Scene {

public:
    std::vector<Entity*> entities;
    unsigned int index_count;
    Scene();

    void addEntity(Entity& entity);
    void bindEntities();
    void reBindEntities();

};



#endif //SCENE_H
