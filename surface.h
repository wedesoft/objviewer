#pragma once
#include <GL/gl.h>
#include "vertex.h"
#include "normal.h"


typedef struct {
  int n_array;
  GLfloat *array;
  int n_indices;
  int *vertex_index;
} surface_t;

surface_t *make_surface(int max_array, int max_indices);

void add_vertex(surface_t *surface, vertex_t vertex);

void add_normal(surface_t *surface, normal_t normal);
