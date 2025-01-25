#include "mesh.h"


Mesh::Mesh(std::vector<float>* vertices_, Shader& shader_, std::vector<unsigned int>* index_buffer_) :
    shader(shader_),
    vertices(vertices_),
    index_buffer(index_buffer_),
    program(createProgram(shader.vertex_shader_source, shader.fragment_shader_source)),
    render_vertices_ptrs(vertices_->size()),
    x_vec(vertices_->size() / 2),
    y_vec(vertices_->size() / 2),
    x_vec_orig(vertices_->size() / 2),
    y_vec_orig(vertices_->size() / 2),
    deref_render(vertices_->size())
    {
    // Copy vertex data to x and y vectors and initialize render vertex as pointers to these
    for (unsigned int i = 0; i < vertices->size() / 2; ++i) {
        x_vec[i] = vertices->data()[i*2];
        y_vec[i] = vertices->data()[i*2 + 1];
        x_vec_orig[i] = vertices->data()[i*2];
        y_vec_orig[i] = vertices->data()[i*2 + 1];

        render_vertices_ptrs[i*2] = &(x_vec[i]);
        render_vertices_ptrs[i*2 + 1] = &(y_vec[i]);
    }
}

void Mesh::bindToGPU() {
    derefEigenVector();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, deref_render.size() * sizeof(float), deref_render.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer->size() * sizeof(unsigned int), index_buffer->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, shader.vertex_size, GL_FLOAT, GL_FALSE, shader.vertex_float_stride, (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(program);
}

void Mesh::reBindMeshToGPU() {
    derefEigenVector();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, deref_render.size() * sizeof(float), deref_render.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer->size() * sizeof(unsigned int), index_buffer->data(), GL_STATIC_DRAW);
}

void Mesh::reBindToGPU() {
    reBindMeshToGPU();
    glUseProgram(program);
}

void Mesh::reBindToGPU(GLuint program) {
    reBindToGPU();
    glUseProgram(program);
}

void Mesh::derefEigenVector() {
    for (unsigned int i = 0; i < render_vertices_ptrs.size(); ++i) {
        deref_render[i] = *(render_vertices_ptrs[i]);
    }
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

void Mesh::move(float x, float y) {
    x_vec = x_vec.array() + x;
    y_vec = y_vec.array() + y;
}
