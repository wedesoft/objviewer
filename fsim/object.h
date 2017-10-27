#pragma once
#include "vertex_array_object.h"
#include "list.h"


typedef struct {
  char *name;
  list_t *vertex_array_object;
} object_t;

object_t *make_object(const char *name);

object_t *add_vertex_array_object(object_t *object, vertex_array_object_t *vertex_array_object);

void draw_elements(vertex_array_object_t *vertex_array_object);

void render(object_t *object);
