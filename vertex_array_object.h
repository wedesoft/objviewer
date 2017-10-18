#pragma once
#include <GL/gl.h>
#include "program.h"
#include "texture.h"


typedef struct {
  program_t *program;
  GLuint vertex_array_object;
  GLuint vertex_buffer_object;
  GLuint element_buffer_object;
  int n_indices;
  int n_textures;
  texture_t **texture;
} vertex_array_object_t;
