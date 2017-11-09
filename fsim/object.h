#pragma once
#include "group.h"
#include "list.h"


typedef struct {
  char *name;
  list_t *group;
} object_t;

object_t *make_object(const char *name);

object_t *add_group(object_t *object, group_t *group);
