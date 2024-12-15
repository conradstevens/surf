#ifndef BALL_H
#define BALL_H
#include "shader.h"
#include "mesh.h"


class Ball {
public:
    Shader shader;
    Mesh mesh;
    Ball();

protected:
    Shader initShader();
    Mesh initMesh();

};


#endif //BALL_H
