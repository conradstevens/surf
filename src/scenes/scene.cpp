// #include "scenes/scene.h"
// #include <thread>
//
//
// Scene::~Scene() {
//     std::for_each(entities.begin(), entities.end(),
//         [](Entity* entity) {delete entity;});
//     entities.clear();
// }
//
// template <EntityDerived... EntityTypes>
// template <EntityDerived Entity_T>
// void Scene::spawn() {
//     using MeshType = Mesh<Entity_T::mesh_size, Entity_T::buffer_size>;
//     MeshType mesh = mesh_loader.getMesh<Entity_T>();
//     auto* entity = new Entity_T(mesh);
//     entities.push_back(entity);
// }
//
// void Scene::deleteEntity(Entity* entity) {
//     auto it = std::find(entities.begin(), entities.end(), entity);
//     if (it != entities.end()) {
//         entities.erase(it);
//         delete entity;
//     }
// }
//
// void Scene::render() {
//     frame_count ++;
//     time_now = std::chrono::high_resolution_clock::now();
//     time_step = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - time_last).count();
//
//     step(time_step);
//
//     for (Entity* entity : entities) {
//         entity->step(time_step);
//         entity->mesh.reBindMeshToGPU();
//         glDrawElements(GL_TRIANGLES, entity->getBufferSize_virtual(), GL_UNSIGNED_INT, nullptr);
//     }
//     time_last = std::chrono::high_resolution_clock::now();
//     std::this_thread::sleep_for(std::chrono::milliseconds(0));
//
//     // Calculate fps
//     if (std::chrono::duration_cast<std::chrono::milliseconds>(time_now - fps_time_last).count() > 1000) {
//         std::cout << "\rFPS: " << frame_count << std::flush;
//         frame_count = 0;
//         fps_time_last = std::chrono::high_resolution_clock::now();
//     }
// }
//
// void Scene::start() {
//     time_last = std::chrono::high_resolution_clock::now();
//     fps_time_last = std::chrono::high_resolution_clock::now();
//     for (Entity* entity : entities) {
//         entity->mesh.bindToGPU();
//     }
// }
//
//
//
// // void Scene::addEntity(Entity* entity, float x, float y) {
// //     entity->setPosition(x, y);
// //     entity->mesh.bindToGPU();
// //     entities.push_back(entity);
// // }
