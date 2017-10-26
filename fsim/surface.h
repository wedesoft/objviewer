#pragma once
#include <stdarg.h>
#include <GL/gl.h>
#include "list.h"


typedef struct {
  list_t array;
  list_t vertex_index;
} surface_t;

surface_t *make_surface(void);

void add_vertex_data(surface_t *surface, int n, ...);

int size_of_array(surface_t *surface);

int size_of_indices(surface_t *surface);

void add_polygon(surface_t *surface, int n, ...);
