#ifndef MESH_H
#define MESH_H
#define GL_SILENCE_DEPRECATION
#include <iostream>
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE  //  Ensures gl3.h is included rather than gl.h
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <Eigen/Dense>
#include <functional>
#include "shader.h"
#include <cmath>
#include "../entities/loc.h"


 /**
  * @brief Determines where the entity will be rendered on the screen given the mesh vertices of an object
  * @param v_Size number of vertices @note v_Size must be an even number
  * @note shader and vertices are past in as references and are thus made const
  */
 template <std::size_t v_size, std::size_t b_size>
 class Mesh {
 protected:
  /**
   * @brief Protected member variables for mesh rendering
   * @param shader the shader the object (shared among objects by reference thus made const)
   * @param index_buffer what order to render the vertices (shared among objects by reference thus made const)
   * @param x_vert, y_vert the subdivided vertices that are referenced by render_vertices
   * @param render_vertices the vertices rendered stored as an array of references to x_vert, y_vert
   * @param program shader program
   * @param VAO vertex array object
   * @param VBO vertex buffer object
   * @param ibo index buffer object
   */
  const Shader shader{};
  const std::array<float, b_size> index_buffer{};
  Eigen::Matrix<float, v_size / 2, 1> x_vert{};
  Eigen::Matrix<float, v_size / 2, 1> y_vert{};
  std::array<std::reference_wrapper<float>, v_size> render_vertices{};
  GLuint program{};
  GLuint VAO{};
  GLuint VBO{};
  GLuint ibo{};

 public:
  /**
   * @brief Constructors initializes all above data members
   * @note Giving the x and y vertices will result in slightly more efficient copying
   */
  Mesh() = default;

  /**
   * @brief Constructor given all values to be initialized
   * @param shader_ Shader set by reference
   * @param index_buffer_ index buffer set by reference
   * @param x_vert_ x vertices copied to allow manipulation
   * @param y_vert_ y vertices copied to allow manipulation
   */
  Mesh(const Shader& shader_, const std::array<float, b_size>& index_buffer_,
       Eigen::Matrix<float, v_size / 2, 1> x_vert_, Eigen::Matrix<float, v_size / 2, 1>  y_vert_);

  /**
   * @brief Constructor given shader, index buffer and full vertex not segmented
   * @param shader_ Shader set by reference
   * @param index_buffer_ index buffer set by reference
   * @param vert_ full vertex not segmented
   */
  Mesh(const Shader& shader_, const std::array<float, b_size>& index_buffer_, const std::array<float, v_size>& vert_);

  /**
   * @brief Compile the vertex or fragment shader program
   * @throw warning given failures to compile
   * @param type
   * @param source
   * @return
   */
  static GLuint compileShader(unsigned int type, const char* source);

  /**
   * @biref Create the shader program given the vertex and buffer size and shader
   * @param vertex_shader_source
   * @param fragment_shader_source
   * @return a pointer to the compiled shader
   */
  GLuint createProgram(const char* vertex_shader_source, const char* fragment_shader_source);

  /**
   * @brief Load the meshes to the GPU for the first time
   */
  void bindToGPU();

  /**
   * @brief Rebind mesh to the GPUs memory
   */
  void reBindMeshToGPU();

  /**
   * @brief Rebind Mesh to GPU and activate the shader
   */
  void reBindToGPU();

  /**
   * @brief rebind Mesh to GPU and activate the shader `program`
   * @param program program to activate
   */
  void reBindToGPU(GLuint program);

  /**
   * @brief Parses and returns the x or y elements of vert depending on the axis provided.
   * The method is made static optionally parse and contain the elements statically in an entity
   * @param vert the original vertices
   * @param axis the axis chosen to isolate
   * @return x_vert_orig values or y_vert_orig as specified by axis
   */
  static auto getVectorByAxis(const std::array<float, v_size> &vert, const Axis &axis)
     -> Eigen::Matrix<float, v_size / 2, 1>;

  /// Kinematics

  /**
   * TODO @brief Move the vertices to render them in a new location
   * @param x translation in x direction
   * @param y translation in y direction
   */
  void move(float x, float y);

  /**
   * TODO @brief Rotate the vertex to render a new orientation
   * @param angle translation angle (radians)
   */
  void rotate(float angle);

  /**
   * TODO @brief Scale the mesh
   * @param s by how much to scale the mesh as a decimal
   */
  void scale(float s);

 };

#endif //MESH_H
