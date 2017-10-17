#pragma once
#include <GL/gl.h>


typedef struct {
  int n_array;
  GLfloat *array;
  int n_indices;
  int *vertex_index;
} surface_t;

surface_t *make_surface(int max_array, int max_indices);
