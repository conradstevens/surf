#ifndef BALL_H
#define BALL_H
#include <cmath>
#include "entity.h"
#include <iostream>
#include <ostream>
#include "shader.h"
#include "mesh.h"


class Ball : public Entity{
private:
    // reused at such a high frequency, worth keeping
    // memory allocation out of function scope

protected:
    static const char* vertexShaderSource_static;
    static const char* fragmentShaderSource_static;
    static std::vector<float>* vertices_static;
    static std::vector<unsigned int>* index_buffer_static;
    static std::vector<float>* x_splice;
    static std::vector<float>* y_splice;

    std::vector<float> direction;
    float speed;  // percent to move across the screen in 1 millisecond

public:
    static Shader shader_static;

    static void load();
    static void unload();
    Ball();

    void step(long time) override;


};


#endif //BALL_H
