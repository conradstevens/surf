#ifndef SHADER_H
#define SHADER_H


class Shader {
public:
  const char *vertex_shader_source{},  *fragment_shader_source{};
  int vertex_size{};
  int vertex_float_stride{};

  explicit Shader(const char* vertex_shader_source, const char* fragment_shader_source, int vertex_size);
};


#endif //SHADER_H
