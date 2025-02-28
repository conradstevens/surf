#ifndef BALL_H
#define BALL_H
#include "entity.h"
#include "../rendering/mesh.h"


/**
 * @brief A basic entity with kinematic properties
 */
class Ball final : public Entity{

public:
     /**
      * @param mesh_size size of ball mesh
      */
     static constexpr size_t mesh_size = 8;
     static constexpr size_t buffer_size = 6;
     Mesh<mesh_size, buffer_size> mesh;

    /**
      * @brief Getter for static data member method mesh_size
      * @return mesh size
      */
    GLsizei getMeshSize_virtual() override {return mesh_size;}

    /**
     * @brief Getter for static data member method buffer_size
     * @return buffer size
     */
    GLsizei getBufferSize_virtual() override {return buffer_size;}

     /**
      * Constructor giving object a new mesh copied from mesh_
      * @param mesh_ the mesh to be copied over
      */
     explicit Ball(Mesh<mesh_size, buffer_size> mesh_);

     /**
      * @brief Static method present in all entities used to get rendering resources
      * @return the Shader Mesh Pair that is used for resourcing
      */
     static Mesh<mesh_size, buffer_size> getResources();

     /**
      * Update state of ball following
      * @param time time passed in frame
      */
     void step(long time) override;
};

template class Mesh<Ball::mesh_size, Ball::buffer_size>;


#endif //BALL_H
