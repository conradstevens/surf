#include "entities/ball.h"


Ball::Ball(Mesh<mesh_size, buffer_size> mesh_) :
    mesh{std::move(mesh_)} {
}

void Ball::step(long time) {
}

Mesh<Ball::mesh_size, Ball::buffer_size> Ball::getResources() {
    const char* vertexShaderSource =
        "#version 410 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource_static =
        "#version 410 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.0f, 0.5f, 1.0f, 1.0f);\n"
        "}\0";

    Shader shader_resource{vertexShaderSource, fragmentShaderSource_static, 2};

    std::array<float, buffer_size> index_buffer =
        {0, 1, 2,
         2, 3, 0};

    Eigen::Matrix<float, mesh_size / 2, 1> x_vert =
        {-0.05f,
          0.05f,
          0.05f,
         -0.05f};

    Eigen::Matrix<float, mesh_size / 2, 1> y_vert =
        {-0.05f,
         -0.05f,
          0.05f,
          0.05f};

    Mesh<mesh_size, buffer_size> mesh_resource{shader_resource, index_buffer, x_vert, y_vert};
    return mesh_resource;
}

