#include <string.h>
#include <GL/glew.h>
#include <gc.h>
#include "object.h"


object_t *make_object(const char *name)
{
  object_t *retval = GC_MALLOC(sizeof(object_t));
  retval->name = GC_MALLOC_ATOMIC(strlen(name) + 1);
  strcpy(retval->name, name);
  retval->group = make_list();
  return retval;
}

object_t *add_group(object_t *object, group_t *group)
{
  append_pointer(object->group, group);
  return object;
}
