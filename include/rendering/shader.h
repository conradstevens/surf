#ifndef SHADER_H
#define SHADER_H

/**
 * @brief loads and stores the shader data members of an object
 * @note Shaders are often static across an object as they are the same for all instances
 */
struct Shader {
    /**
     * @param vertex_shader_source the vertex shader of an object
     * @param fragment_shader_source the vertex shader of an object
     * @param vertex_size How many values make up each vertex position
     * @param vertex_float_stride the size in bytes of a vertex
     *
     * @note vertex values must occupy 4 bytes.
     */
    const char *vertex_shader_source{},  *fragment_shader_source{};
    int vertex_size{};
    int vertex_float_stride{};

    /**
     * Constructor simply initializes types
     * The Default constructor sets these to small default values.
     */
    explicit Shader(const char* vertex_shader_source, const char* fragment_shader_source, int vertex_size) :
        vertex_shader_source(vertex_shader_source),
        fragment_shader_source(fragment_shader_source),
        vertex_size(vertex_size),
        vertex_float_stride(vertex_size * static_cast<int>(sizeof(float))){}
    Shader() = default;
};


#endif //SHADER_H