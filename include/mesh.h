#ifndef MESH_H
#define MESH_H
#define GL_SILENCE_DEPRECATION
#include <iostream>
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE  //  Ensures gl3.h is included rather than gl.h
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <vector>
#include <Eigen/Dense>
#include "shader.h"
#include <cmath>

/**
 * @brief The mesh vertices of an object
 * Determines where the entity will be rendered on the screen
 * @note shader and vertices are often static across entities of the same type
 */
class Mesh {
public:
    /**
     * @param shader the shader the object (often shared)
     * @param vertices the original vertices of the object
     * @param index_buffer what order to render the vertices
     * @param render_vertices_ptrs the rendered vertex pointers as shown on screen
     * @param deref_render the dereferenced rendered vertex pointers as shown on screen
     * @param x_vec, y_vec the set of vertex data in each coordinates as shown on screen before scaling
     * @param x_vec_orig, y_vec_orig the original set of vertex data in their respective coordinates
     * @param x_vec_scaled, y_vec_scaled the moved and scaled vertices each coordinate as shown on screen
     *
     * ##### Open GL data members #####
     * TODO Describe these
     * @param program
     * @param VAO
     * @param VBO
     * @param ibo
     */
    // Shared across entities of same type
    Shader shader{};
    std::vector<float>* vertices = nullptr;
    std::vector<unsigned int>* index_buffer{};

    // Unique to individual meshes
    std::vector<float*> render_vertices_ptrs{};
    std::vector<float> deref_render{};
    Eigen::VectorXf x_vec{};
    Eigen::VectorXf y_vec{};
    Eigen::VectorXf x_vec_orig{};
    Eigen::VectorXf y_vec_orig{};
    Eigen::VectorXf x_vec_scaled{};
    Eigen::VectorXf y_vec_scaled{};

    GLuint program{}, VAO{}, VBO{}, ibo{};

    Mesh() = default;
    Mesh(std::vector<float>* vertices_, Shader &shader_, std::vector<unsigned int>* index_buffer_);


    static unsigned int compileShader(unsigned int type, const char* source);
    GLuint createProgram(const char* vertex_shader_source, const char* fragment_shader_source);

    void move(float x, float y);
    void rotate(float angle);

    void bindToGPU();
    void reBindMeshToGPU();
    void reBindToGPU();
    void reBindToGPU(GLuint program);

protected:
    void derefEigenVector();

};


#endif //MESH_H