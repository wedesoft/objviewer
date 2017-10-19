#pragma once
#include <GL/gl.h>


typedef struct
{
  GLfloat u;
  GLfloat v;
} texture_coordinate_t;

texture_coordinate_t make_texture_coordinate(GLfloat u, GLfloat v);
