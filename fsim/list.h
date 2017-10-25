#pragma once
#include <GL/gl.h>

typedef struct {
  int size;
  int buffer_size;
  GLuint *element;
} list_t;

list_t make_list(void);

void append_gluint(list_t *list, GLuint value);

inline GLuint *get_gluint(list_t *list)
{
  return &list->element[0];
}
