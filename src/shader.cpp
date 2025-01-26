#include "shader.h"


Shader::Shader(const char* vertex_shader_source, const char* fragment_shader_source, int vertex_size) :
    vertex_shader_source(vertex_shader_source),
    fragment_shader_source(fragment_shader_source),
    vertex_size(vertex_size),
    vertex_float_stride(vertex_size * sizeof(float)){
}

