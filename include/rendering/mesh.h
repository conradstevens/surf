#ifndef MESH_H
#define MESH_H
#define GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE  //  Ensures gl3.h is included rather than gl.h
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <iostream>
#include <Eigen/Dense>
#include "shader.h"
#include "rendering/mesh.h"
#include "entities/loc.h"


/**
* @brief Determines where the entity will be rendered on the screen given the mesh vertices of an object
* @param v_Size number of vertices @note v_Size must be an even number
* @note shader and vertices are past in as references and are thus made const
*/
template <std::size_t v_size, std::size_t b_size>
class Mesh {
protected:
    /**
    * @brief Protected member variables for mesh rendering
    * @param shader the shader the object (shared among objects by reference thus made const)
    * @param index_buffer what order to render the vertices (shared among objects by reference thus made const)
    * @param x_vert, y_vert the subdivided vertices that are referenced by render_vertices
    * @param render_vertices the vertices rendered stored as an array of references to x_vert, y_vert
    * @param program shader program
    * @param VAO vertex array object
    * @param VBO vertex buffer object
    * @param ibo index buffer object
    */
    const Shader shader{};
    const std::array<float, b_size> index_buffer{};
    Eigen::Matrix<float, v_size / 2, 1> x_vert{};
    Eigen::Matrix<float, v_size / 2, 1> y_vert{};
    std::array<std::reference_wrapper<float>, v_size> render_vert{};
    GLuint program{};
    GLuint VAO{};
    GLuint VBO{};
    GLuint ibo{};

    public:
    /**
    * @brief Constructors initializes all above data members
    * @note Giving the x and y vertices will result in slightly more efficient copying
    */
    Mesh() = default;

    /**
    * @brief Constructor given all values to be initialized
    * @param shader_ Shader set by reference
    * @param index_buffer_ index buffer set by reference
    * @param x_vert_ x vertices copied to allow manipulation
    * @param y_vert_ y vertices copied to allow manipulation
    */
    Mesh(const Shader& shader_, const std::array<float, b_size>& index_buffer_,
    Eigen::Matrix<float, v_size / 2, 1> x_vert_, Eigen::Matrix<float, v_size / 2, 1>  y_vert_);

    /**
    * @brief Constructor given shader, index buffer and full vertex not segmented
    * @param shader_ Shader set by reference
    * @param index_buffer_ index buffer set by reference
    * @param vert_ full vertex not segmented
    */
    Mesh(const Shader& shader_, const std::array<float, b_size>& index_buffer_, const std::array<float, v_size>& vert_);

    /**
     * @brief Initialize a std::array of float references. The references themselves can be changed but as per the
     * standard, they cannot change what they refer to.
     * @note when initialized it will refer to dangling references of the array_dummy array.
     * @tparam Is template parameter pack to replicate arr[1], arr[2], ...
     * @return array of dangling float references
     */
    template<std::size_t... Is>
    auto initRefArray(std::index_sequence<Is...>) -> std::array<std::reference_wrapper<float>, v_size>;

    /**
    * @brief Compile the vertex or fragment shader program
    * @throw warning given failures to compile
    * @param type
    * @param source
    * @return
    */
    static GLuint compileShader(unsigned int type, const char* source);

    /**
    * @biref Create the shader program given the vertex and buffer size and shader
    * @param vertex_shader_source
    * @param fragment_shader_source
    * @return a pointer to the compiled shader
    */
    GLuint createProgram(const char* vertex_shader_source, const char* fragment_shader_source);

    /**
    * @brief Load the meshes to the GPU for the first time
    */
    void bindToGPU();

    /**
    * @brief Rebind mesh to the GPUs memory
    */
    void reBindMeshToGPU();

    /**
    * @brief Rebind Mesh to GPU and activate the shader
    */
    void reBindToGPU();

    /**
    * @brief rebind Mesh to GPU and activate the shader `program`
    * @param program program to activate
    */
    void reBindToGPU(GLuint program);

    /**
    * @brief Parses and returns the x or y elements of vert depending on the axis provided.
    * The method is made static optionally parse and contain the elements statically in an entity
    * @param vert the original vertices
    * @param axis the axis chosen to isolate
    * @return x_vert_orig values or y_vert_orig as specified by axis
    */
    static auto getVectorByAxis(const std::array<float, v_size> &vert, const Axis &axis)
    -> Eigen::Matrix<float, v_size / 2, 1>;

    /// Kinematics

    /**
    * TODO @brief Move the vertices to render them in a new location
    * @param x translation in x direction
    * @param y translation in y direction
    */
    void move(float x, float y);

    /**
    * TODO @brief Rotate the vertex to render a new orientation
    * @param angle translation angle (radians)
    */
    void rotate(float angle);

    /**
    * TODO @brief Scale the mesh
    * @param s by how much to scale the mesh as a decimal
    */
    void scale(float s);

 };


template <std::size_t v_size, std::size_t b_size>
Mesh<v_size, b_size>::Mesh(const Shader& shader_, const std::array<float, b_size>& index_buffer_,
       Eigen::Matrix<float, v_size / 2, 1> x_vert_, Eigen::Matrix<float, v_size / 2, 1>  y_vert_):
    shader{shader_},
    index_buffer{index_buffer_},
    x_vert{x_vert_},
    y_vert{y_vert_},
    render_vert{initRefArray(std::make_index_sequence<v_size>{})}{
    for (size_t i = 0; i < v_size / 2; ++i) {
        render_vert[i*2]     = std::ref(x_vert[i]);
        render_vert[i*2 + 1] = std::ref(y_vert[i]);
    }
}

template <std::size_t v_size, std::size_t b_size>
Mesh<v_size, b_size>::Mesh(const Shader& shader_, const std::array<float, b_size>& index_buffer_, const std::array<float, v_size> &vert_) :
    shader{shader_},
    index_buffer{index_buffer_},
    render_vert(initRefArray(std::make_index_sequence<v_size>{})){
    for (size_t i = 1; i < v_size; ++(++i)) {
        x_vert[i - 1] = vert_[i - 1];
        x_vert[i]     = vert_[i];
        render_vert[i*2]     = std::ref(x_vert[i]);
        render_vert[i*2 + 1] = std::ref(y_vert[i]);
    }
}

template<std::size_t v_size, std::size_t b_size>
template<std::size_t... Is>
auto Mesh<v_size, b_size>::initRefArray(std::index_sequence<Is...>) -> std::array<std::reference_wrapper<float>, v_size>{
    std::array<float, v_size> dummy_array{};
    std::array<std::reference_wrapper<float>, v_size> render_vert_ = {dummy_array[Is]...};
    return render_vert_;
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
    glBufferData(GL_ARRAY_BUFFER, v_size * sizeof(float), render_vert.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer.size() * sizeof(unsigned int),
        index_buffer.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, shader.vertex_size, GL_FLOAT, GL_FALSE, shader.vertex_float_stride,
        (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(program);
}

template <std::size_t v_size, std::size_t b_size>
void Mesh<v_size, b_size>::reBindMeshToGPU() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, v_size * sizeof(float), render_vert.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer.size() * sizeof(unsigned int),
        index_buffer.data(), GL_STATIC_DRAW);
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

#endif //MESH_H
