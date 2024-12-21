#ifndef BALL_H
#define BALL_H
#include "shader.h"
#include "mesh.h"
#include "entity.h"

// class Ball : public entity{
class Ball {

protected:
    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    std::vector<float> vertices;
    std::vector<unsigned int> index_buffer;
    Shader initShader();
    Mesh initMesh();

public:
    Shader shader;
    Mesh mesh;
    Ball();

};


#endif //BALL_H
