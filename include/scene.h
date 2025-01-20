#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "entity.h"

class Scene {

public:
    std::vector<Entity> entities;
    unsigned int index_count;
    Scene();

    void addEntity(Entity entity);
    void bindEntities();

};



#endif //SCENE_H
