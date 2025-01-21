#include <iostream>
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE  //  Ensures gl3.h is included rather than gl.h
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <OpenGL/gl3.h>
#include "mesh.h"


Mesh::Mesh(std::vector<float>* vertices, Shader& shader, std::vector<unsigned int>* index_buffer) :
    shader(shader),
    vertices(vertices),
    program(createProgram(shader.vertex_shader_source, shader.fragment_shader_source)),
    index_buffer(index_buffer){
}

void Mesh::bindToGPU() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float), vertices->data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer->size() * sizeof(unsigned int), index_buffer->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, shader.vertex_size, GL_FLOAT, GL_FALSE, shader.vertex_float_stride, (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(program);
}

GLuint Mesh::createProgram(const char* vertex_shader_source, const char* fragment_shader_source) {
    GLuint _program = glCreateProgram();
    GLuint vertex_shader = compileShader(GL_VERTEX_SHADER, vertex_shader_source);
    GLuint fragment_shader = compileShader(GL_FRAGMENT_SHADER, fragment_shader_source);

    glAttachShader(_program, vertex_shader);
    glAttachShader(_program, fragment_shader);
    glLinkProgram(_program);
    glValidateProgram(_program);

    int result;
    glGetProgramiv(_program, GL_LINK_STATUS, &result);
    if(result == GL_FALSE) {
        int length;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetProgramInfoLog(_program, length, &length, message);
        std::cout << "Failed to compile program" << std::endl;
        std::cout << message << std::endl;
        glDeleteProgram(_program);
    }
    glDeleteProgram(vertex_shader);
    glDeleteProgram(fragment_shader);
    return _program;
}

GLuint Mesh::compileShader(const GLuint type, const char* source) {
    const GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment ") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
    }
    return id;
}