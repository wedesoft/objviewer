#pragma once
#include <GL/gl.h>
#include "program.h"
#include "surface.h"
#include "texture.h"
#include "image.h"
#include "list.h"


typedef struct {
  program_t *program;
  GLuint vertex_array_object;
  GLuint vertex_buffer_object;
  GLuint element_buffer_object;
  int n_indices;
  list_t *texture;
} vertex_array_object_t;

vertex_array_object_t *make_vertex_array_object(program_t *program, surface_t *surface);

void setup_vertex_attribute_pointer(vertex_array_object_t *vertex_array_object, const char *attribute, int size, int stride);

void add_texture(vertex_array_object_t *vertex_array_object, texture_t *texture, image_t *image);
