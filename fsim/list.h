#pragma once
#include <GL/gl.h>

typedef struct {
  int size;
  int buffer_size;
  GLuint *element;
} list_t;

list_t make_list(void);

void list_append_gluint(list_t *list, GLuint value);

GLuint *get_gluint(list_t *list);
