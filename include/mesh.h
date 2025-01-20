#ifndef MESH_H
#define MESH_H
#define GL_SILENCE_DEPRECATION
#include <vector>
#include "shader.h"
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3

class Mesh {
public:
    Shader shader;
    std::vector<float> vertices;
    std::vector<unsigned int> index_buffer;
    GLuint program, VAO, VBO, ibo;

    Mesh(std::vector<float> &vertices, Shader &shader, std::vector<unsigned int> &index_buffer);
    Mesh() = default;

    static unsigned int compileShader(unsigned int type, const char* source);
    std::vector<unsigned int> initIndexBuffer(std::vector<unsigned int>& index_buffer);
    GLuint createProgram(const char* vertex_shader_source, const char* fragment_shader_source);

    void bindToGPU();
};


#endif //MESH_H