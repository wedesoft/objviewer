#pragma once
#include <GL/gl.h>


typedef struct {
  GLfloat x;
  GLfloat y;
  GLfloat z;
} normal_t;

normal_t make_normal(GLfloat x, GLfloat y, GLfloat z);
