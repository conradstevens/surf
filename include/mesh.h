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

class Mesh {
public:
    Shader shader;
    std::vector<float>* vertices;
    std::vector<unsigned int>* index_buffer;

    std::vector<float>* x_splice;
    std::vector<float>* y_splice;
    Eigen::VectorXf x_move;
    Eigen::VectorXf y_move;
    Eigen::VectorXf render_vertices;

    GLuint program, VAO, VBO, ibo;

    Mesh(std::vector<float>* vertices, Shader &shader, std::vector<unsigned int>* index_buffer,
        std::vector<float>* x_splice, std::vector<float>* y_splice);
    Mesh() = default;

    static unsigned int compileShader(unsigned int type, const char* source);
    GLuint createProgram(const char* vertex_shader_source, const char* fragment_shader_source);

    void move(float x, float y);
    void position(float x, float y);

    void bindToGPU();
    void reBindMeshToGPU();
    void reBindToGPU();
    void reBindToGPU(GLuint program);

};


#endif //MESH_H