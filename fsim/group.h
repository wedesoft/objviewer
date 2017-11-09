#pragma once
#include <stdarg.h>
#include <GL/gl.h>
#include "list.h"
#include "material.h"


typedef struct {
  list_t *array;
  list_t *vertex_index;
  int stride;
  material_t *material;
} group_t;

group_t *make_surface(int stride);

void add_vertex_data(group_t *surface, int n, ...);

int size_of_array(group_t *surface);

int size_of_indices(group_t *surface);

void add_triangle(group_t *surface, int index1, int index2, int index3);

void extend_triangle(group_t *surface, int index);

void use_material(group_t *surface, material_t *material);
