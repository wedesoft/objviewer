#pragma once
#include <stdarg.h>
#include <GL/gl.h>
#include "list.h"
#include "material.h"


typedef struct {
  char *name;
  list_t *array;
  list_t *vertex_index;
  int stride;
  material_t *material;
} group_t;

group_t *make_group(const char *name, int stride);

void add_vertex_data(group_t *group, int n, ...);

int size_of_array(group_t *group);

int size_of_indices(group_t *group);

void add_triangle(group_t *group, int index1, int index2, int index3);

void extend_triangle(group_t *group, int index);

void use_material(group_t *group, material_t *material);
