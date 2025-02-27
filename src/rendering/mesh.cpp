#include "rendering/mesh.h"
#include "entities/loc.h"


template <std::size_t v_size, std::size_t b_size>
Mesh<v_size, b_size>::Mesh(const Shader& shader_, const std::array<float, b_size>& index_buffer_,
       Eigen::Matrix<float, v_size / 2, 1> x_vert_, Eigen::Matrix<float, v_size / 2, 1>  y_vert_):
    shader{shader_},
    index_buffer{index_buffer_},
    x_vert{x_vert_},
    y_vert{y_vert_} {
    for (size_t i = 1; i < v_size / 2; ++i) {
        render_vertices[i - 1] = std::ref(x_vert_[i]);
        render_vertices[i]     = std::ref(y_vert_[i]);
    }
}

template <std::size_t v_size, std::size_t b_size>
Mesh<v_size, b_size>::Mesh(const Shader& shader_, const std::array<float, b_size>& index_buffer_, const std::array<float, v_size> &vert_) :
    shader{shader_},
    index_buffer{index_buffer_} {
    for (size_t i = 1; i < v_size; ++(++i)) {
        x_vert[i - 1] = vert_[i - 1];
        x_vert[i]     = vert_[i];
        render_vertices[i - 1] = std::ref(x_vert[i - 1]);
        render_vertices[i]     = std::ref(y_vert[i]);
    }
}

template <std::size_t v_size, std::size_t b_size>
auto Mesh<v_size, b_size>::getVectorByAxis(const std::array<float, v_size> &vert, const Axis& axis)
    -> Eigen::Matrix<float, v_size / 2, 1>  {
    size_t i;
    switch (axis) {
        case Axis::X:
            i = 0;
            break;
        case Axis::Y:
            i = 1;
        break;
        default:
            throw std::invalid_argument("Invalid axis");
    }
    Eigen::Matrix<float, v_size / 2, 1> result{};
    for (; i < v_size / 2; ++(++i)) result[i] = vert[i];
    return result;
}

template <std::size_t v_size, std::size_t b_size>
void Mesh<v_size, b_size>::bindToGPU() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, v_size * sizeof(float), render_vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer->size() * sizeof(unsigned int),
        index_buffer->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, shader.vertex_size, GL_FLOAT, GL_FALSE, shader.vertex_float_stride,
        (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(program);
}

template <std::size_t v_size, std::size_t b_size>
void Mesh<v_size, b_size>::reBindMeshToGPU() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, v_size * sizeof(float), render_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer->size() * sizeof(unsigned int),
        index_buffer->data(), GL_STATIC_DRAW);
}

template <std::size_t v_size, std::size_t b_size>
void Mesh<v_size, b_size>::reBindToGPU() {
    reBindMeshToGPU();
    glUseProgram(program);
}

template <std::size_t v_size, std::size_t b_size>
void Mesh<v_size, b_size>::reBindToGPU(GLuint program) {
    reBindToGPU();
    glUseProgram(program);
}

template <std::size_t v_size, std::size_t b_size>
GLuint Mesh<v_size, b_size>::createProgram(const char* vertex_shader_source, const char* fragment_shader_source) {
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

template <std::size_t v_size, std::size_t b_size>
GLuint Mesh<v_size, b_size>::compileShader(const GLuint type, const char* source) {
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
