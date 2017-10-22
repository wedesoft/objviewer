#pragma once
#include "rgb.h"
#include "vertex_array_object.h"


typedef struct {
  rgb_t background_color;
  int n_vertex_array_objects;
  vertex_array_object_t **vertex_array_object;
} object_t;

object_t *make_object(rgb_t background_color, int max_vertex_array_objects);

object_t *add_vertex_array_object(object_t *object, vertex_array_object_t *vertex_array_object);

void draw_elements(vertex_array_object_t *vertex_array_object);

void render(object_t *object);
