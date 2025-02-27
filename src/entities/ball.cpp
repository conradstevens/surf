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

    std::array<float, Ball::buffer_size> index_buffer =
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

    Mesh<Ball::mesh_size, Ball::buffer_size> mesh_resource{shader_resource, index_buffer, x_vert, y_vert};
    return mesh_resource;
}

//
// Ball::Ball(): Entity(&Ball::shader_static, vertices_static, index_buffer_static,
//         Loc{0.0f, 0.0f, 0.071f, 0.071f}),
//     direction({-1.0f, -2.0f}),
//     speed(0.0005f),
//     rpm(1.0f){
// }
//
// Ball::Ball(float scale_, std::vector<float> direction_, float speed_, float rpm_):
//     Entity(&Ball::shader_static, vertices_static, index_buffer_static,
//         Loc{0.0f, 0.0f, 0.071f * 2, 0.071f * 2}),
//     scale(scale_),
//     direction(std::move(direction_)),
//     speed(speed_),
//     rpm(rpm_){
//     setScale(scale);
// }
//
// void Ball::step(long time) {
//     // Move
//     float move_increment = time * speed;
//     float angle = atan(direction[1] / direction[0]);
//     float x_increment = move_increment * cos(angle);
//     float y_increment = move_increment * sin(angle);
//
//     x_increment = fabs(x_increment);
//     y_increment = fabs(y_increment);
//
//     if (direction[0] < 0.0f) {
//         x_increment = -x_increment;
//     } if (direction[1] < 0.0f) {
//         y_increment = -y_increment;
//     }
//
//     move(x_increment, y_increment);
//
//     // Rotate
//     float rotation_step = rpm * time / 1000 * 2 * 3.14159265f;
//     loc.angle += rotation_step;
//     rotate(loc.angle);
// }
//

