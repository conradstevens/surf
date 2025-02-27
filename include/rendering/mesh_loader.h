#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <unordered_map>
#include <typeindex>

#include "mesh.h"
#include "../entities/entity.h"

/**
 * @brief Tuple wrapper to manage entity meshes
 * @param entity_meshes defined at Scene initialization keeps track of meshes in the scene.
 */
class MeshLoader {
    /**
     * @brief Data members to keep track of different mesh types
     * @param entityMeshes tuple of different sized meshes
     */
    std::tuple<> entity_meshes = {};

public:
    /**
     * @brief Append a list of types at construction
     * @tparam Types
     */
    template <EntityDerived... Types>
    MeshLoader() {
        (appendMesh<Types>(), ...);
    }

    /**
     * @brief Add type to data structure
     * @tparam Entity_T
     */
    template <EntityDerived Entity_T>
    void appendMesh() {
        using MeshType = Mesh<Entity_T::getBufferSize(), Entity_T::getMeshSize()>;
        MeshType new_mesh = Entity_T::getResources();
        entity_meshes = std::tuple_cat(entity_meshes, std::make_tuple(new_mesh));
    }

    /**
     * @brief get type from the data structure
     * @tparam Entity_T entity type
     */
    template <EntityDerived Entity_T>
    auto getMesh() -> Mesh<Entity_T::getBufferSize(), Entity_T::getMeshSize()>& {
        using MeshType = Mesh<Entity_T::getBufferSize(), Entity_T::getMeshSize()>;
        return std::get<MeshType>(entity_meshes);
    }
};


#endif //MESHLOADER_H
