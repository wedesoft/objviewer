#pragma once
#include "surface.h"
#include "list.h"


typedef struct {
  char *name;
  list_t *surface;
} object_t;

object_t *make_object(const char *name);

object_t *add_surface(object_t *object, surface_t *surface);
