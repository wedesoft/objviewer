#pragma once
#include <stdarg.h>
#include <GL/gl.h>
#include "list.h"


typedef struct {
  list_t array;
  list_t vertex_index;
} surface_t;

surface_t *make_surface(void);

void add_vertex(surface_t *surface, GLfloat x, GLfloat y, GLfloat z);

void add_normal(surface_t *surface, GLfloat x, GLfloat y, GLfloat z);

void add_texture_coordinate(surface_t *surface, GLfloat u, GLfloat v);

int size_of_array(surface_t *surface);

int size_of_indices(surface_t *surface);

void add_polygon(surface_t *surface, int n, ...);
