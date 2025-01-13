#ifndef ENTITY_H
#define ENTITY_H
#include "shader.h"
#include "mesh.h"


struct Pos {
    float x;
    float y;
    Pos(float _x=0.0f, float _y=0.0f) : x(_x), y(_y) {}
};

class Entity {

protected:
    Shader initShader(const char* vertexShaderSource, const char* fragmentShaderSource);
    Shader initShader();
    virtual Mesh initMesh(std::vector<float> vertices, std::vector<unsigned int> index_buffer);
    virtual Mesh initMesh();

public:
    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    std::vector<float> vertices;
    std::vector<unsigned int> index_buffer;
    Shader shader;
    Mesh mesh;

    // Constructors
    Entity(Shader shader, Mesh mesh);
    Entity(const char* vertexShaderSource_,
           const char* fragmentShaderSource_,
           std::vector<float> vertices_,
           std::vector<unsigned int> index_buffer_);
};


#endif //ENTITY_H
