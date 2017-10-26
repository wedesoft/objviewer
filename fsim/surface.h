#pragma once
#include <stdarg.h>
#include <GL/gl.h>
#include "vertex.h"
#include "normal.h"
#include "texture_coordinate.h"
#include "list.h"


typedef struct {
  list_t array;
  list_t vertex_index;
} surface_t;

surface_t *make_surface(void);

void add_vertex(surface_t *surface, vertex_t vertex);

void add_normal(surface_t *surface, normal_t normal);

void add_texture_coordinate(surface_t *surface, texture_coordinate_t texture_coordinate);

int size_of_array(surface_t *surface);

int size_of_indices(surface_t *surface);

void add_polygon(surface_t *surface, int n, ...);
