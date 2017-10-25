#pragma once
#include <GL/gl.h>

typedef struct {
  int size;
  int buffer_size;
  void *element;
} list_t;

list_t make_list(void);

void append_gluint(list_t *list, GLuint value);

void append_glfloat(list_t *list, GLfloat value);

inline GLuint *get_gluint(list_t *list) { return (GLuint *)list->element; }

inline GLfloat *get_glfloat(list_t *list) { return (GLfloat *)list->element; }
