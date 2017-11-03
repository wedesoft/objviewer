#pragma once
#include <stdarg.h>
#include <GL/gl.h>
#include "list.h"


typedef struct {
  list_t *array;
  list_t *vertex_index;
  int stride;
} surface_t;

surface_t *make_surface(int stride);

void add_vertex_data(surface_t *surface, int n, ...);

int size_of_array(surface_t *surface);

int size_of_indices(surface_t *surface);

void add_triangle(surface_t *surface, int index1, int index2, int index3);

void extend_triangle(surface_t *surface, int index);
