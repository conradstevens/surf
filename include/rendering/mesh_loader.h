// #ifndef MESHLOADER_H
// #define MESHLOADER_H
//
// #include "mesh.h"
// #include "../entities/entity.h"
//
// /**
//  * @brief Tuple wrapper to manage entity meshes
//  * @param entity_meshes defined at Scene initialization keeps track of meshes in the scene.
//  */
// template <EntityDerived... Types>
// class MeshLoader {
//     /**
//      * @brief Data members to keep track of different mesh types
//      * @param entityMeshes tuple of different sized meshes
//      */
//     std::tuple<Types...> entity_meshes{Types::getResources()...};
//
// public:
//     /**
//      * @brief Append a list of types at construction
//      * @tparam Types
//      */
//     MeshLoader() = default;
//
//     /**
//      * @brief get type from the data structure
//      * @tparam Entity_T entity type
//      */
//     template <EntityDerived Entity_T>
//     auto getMesh() -> Mesh<Entity_T::mesh_size, Entity_T::buffer_size>& {
//         using MeshType = Mesh<Entity_T::mesh_size, Entity_T::buffer_size>;
//         return std::get<MeshType>(entity_meshes);
//     }
// };
//
//
// #endif //MESHLOADER_H
