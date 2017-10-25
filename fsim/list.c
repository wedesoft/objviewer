#include <string.h>
#include <gc.h>
#include "list.h"

list_t make_list(void)
{
  list_t result;
  result.size = 0;
  result.buffer_size = 0;
  result.element = NULL;
  return result;
}

void list_append_gluint(list_t *list, GLuint value)
{
  if (list->buffer_size < (list->size + 1) * sizeof(GLuint)) {
    list->buffer_size = list->buffer_size ? 2 * list->buffer_size : sizeof(GLuint);
    GLuint *space = GC_MALLOC_ATOMIC(list->buffer_size);
    memcpy(space, list->element, list->size * sizeof(GLuint));
    list->element = space;
  };
  list->element[list->size++] = value;
}

GLuint *get_gluint(list_t *list)
{
  return &list->element[0];
}
