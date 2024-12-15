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
    GLuint program, VAO, VBO;

    explicit Mesh(std::vector<float>& vertices, Shader& shader);

    GLuint createProgram(const char* vertex_shader_source, const char* fragment_shader_source);
    void bindToGPU();

    static unsigned int compileShader(unsigned int type, const char* source);

};


#endif //MESH_H