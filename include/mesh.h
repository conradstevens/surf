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


class Mesh {
public:
    Shader shader;
    std::vector<float>* vertices;
    std::vector<unsigned int>* index_buffer;

    std::vector<float*> render_vertices_ptrs;
    std::vector<float> deref_render;
    Eigen::VectorXf x_vec;
    Eigen::VectorXf y_vec;
    Eigen::VectorXf x_vec_orig;
    Eigen::VectorXf y_vec_orig;
    Eigen::VectorXf x_vec_scaled;
    Eigen::VectorXf y_vec_scaled;

    GLuint program, VAO, VBO, ibo;


    Mesh(std::vector<float>* vertices_, Shader &shader_, std::vector<unsigned int>* index_buffer_);

    Mesh() = default;

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