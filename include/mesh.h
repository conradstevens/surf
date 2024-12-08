#ifndef MESH_H
#define MESH_H

class Mesh {
public:
    GLuint program{};
    GLuint VAO{}, VBO{};

    explicit Mesh(const char* vertex_shader_source, const char* fragment_shader_source, float *vertices, int len_vertices);

    void createProgram(const char* vertex_shader_source, const char* fragment_shader_source);
    void bindToGPU();

    static unsigned int compileShader(unsigned int type, const char* source);

protected:
    float *vertices{};
    int len_vertices{};
    int size_of_vertices{};
};


#endif //MESH_H