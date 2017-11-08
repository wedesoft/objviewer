#pragma once
#include <GL/gl.h>
#include "program.h"
#include "surface.h"
#include "object.h"
#include "texture.h"
#include "material.h"
#include "image.h"
#include "list.h"


typedef struct {
  program_t *program;
  int n_attributes;
  long attribute_pointer;
  GLuint vertex_array_object;
  GLuint vertex_buffer_object;
  GLuint element_buffer_object;
  int n_indices;
  material_t *material;
  list_t *texture;
} vertex_array_object_t;

vertex_array_object_t *make_vertex_array_object(program_t *program, surface_t *surface);

list_t *make_vertex_array_object_list(program_t *program, object_t *object);

void setup_vertex_attribute_pointer(vertex_array_object_t *vertex_array_object, const char *attribute, int size, int stride);

void add_texture(vertex_array_object_t *vertex_array_object, texture_t *texture, image_t *image);

void draw_elements(vertex_array_object_t *vertex_array_object);

void render(list_t *vertex_array_object);
