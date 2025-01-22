#ifndef BALL_H
#define BALL_H
#include "shader.h"
#include "mesh.h"
#include "entity.h"


class Ball : public Entity{
protected:
    static const char* vertexShaderSource_static;
    static const char* fragmentShaderSource_static;
    static std::vector<float>* vertices_static;
    static std::vector<unsigned int>* index_buffer_static;
    static std::vector<float>* x_splice;
    static std::vector<float>* y_splice;

public:
    static Shader shader_static;

    Ball();
    static void load();
    static void unload();
};


#endif //BALL_H
