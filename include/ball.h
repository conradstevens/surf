#ifndef BALL_H
#define BALL_H
#include <cmath>
#include "entity.h"
#include <utility>
#include <iostream>
#include <ostream>
#include "shader.h"
#include "mesh.h"


class Ball : public Entity{

protected:
    // Rendering Data
    static const char* vertexShaderSource_static;
    static const char* fragmentShaderSource_static;
    static std::vector<float>* vertices_static;
    static std::vector<unsigned int>* index_buffer_static;

    // Movement Data
    std::vector<float> direction{0.0f, 0.0f};   // {x, y} direction, treated as unit vector
    float speed{};                              // percent to move across the screen in 1 millisecond
    float rpm{};                                // rotations per second
    float scale{};                              // percent of starting size

public:
    static Shader shader_static;

    static void load();
    static void unload();

    Ball();
    Ball(float scale_, std::vector<float> direction_, float speed_, float rotation_);

    void step(long time) override;
};


#endif //BALL_H
