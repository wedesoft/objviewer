#pragma once
#include <GL/gl.h>
#include "shader.h"


typedef struct {
  shader_t *vertex_shader;
  shader_t *fragment_shader;
  GLuint program;
  int n_attributes;
  long attribute_pointer;
} program_t;
