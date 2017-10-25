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

static void grow_list(list_t *list, int element_size)
{
  if (list->buffer_size < (list->size + 1) * element_size) {
    list->buffer_size = list->buffer_size ? 2 * list->buffer_size : element_size;
    GLuint *space = GC_MALLOC_ATOMIC(list->buffer_size);
    memcpy(space, list->element, list->size * element_size);
    list->element = space;
  };
}

void append_gluint(list_t *list, GLuint value)
{
  grow_list(list, sizeof(GLuint));
  ((GLuint *)list->element)[list->size++] = value;
}

void append_glfloat(list_t *list, GLfloat value)
{
  grow_list(list, sizeof(GLfloat));
  ((GLfloat *)list->element)[list->size++] = value;
}
