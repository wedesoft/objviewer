#pragma once
#include <GL/gl.h>


typedef struct
{
  const char *name;
  GLuint texture;
} texture_t;

texture_t *make_texture(const char *name);
