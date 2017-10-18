#pragma once
#include <GL/gl.h>
#include "program.h"
#include "surface.h"
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

vertex_array_object_t *make_vertex_array_object(program_t *program, surface_t *surface, int max_textures);

void setup_vertex_attribute_pointer(vertex_array_object_t *vertex_array_object, const char *attribute, int size, int stride);
