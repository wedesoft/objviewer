#pragma once
#include <GL/gl.h>
#include "vertex.h"
#include "normal.h"
#include "texture_coordinate.h"


typedef struct {
  int n_array;
  GLfloat *array;
  int n_indices;
  int *vertex_index;
} surface_t;

surface_t *make_surface(int max_array, int max_indices);

void add_vertex(surface_t *surface, vertex_t vertex);

void add_normal(surface_t *surface, normal_t normal);

void add_texture_coordinate(surface_t *surface, texture_coordinate_t texture_coordinate);

int size_of_array(surface_t *surface);

void build_facet(surface_t *surface, int number, int vertex_index);

int size_of_indices(surface_t *surface);
