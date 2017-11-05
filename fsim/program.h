#pragma once
#include <GL/gl.h>
#include "shader.h"


typedef struct {
  shader_t *vertex_shader;
  shader_t *fragment_shader;
  GLuint program;
} program_t;

program_t *make_program(const char *vertex_shader_file_name, const char *fragment_shader_file_name);

void uniform_matrix(program_t *program, const char *name, float *columns);
