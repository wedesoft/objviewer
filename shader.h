#pragma once
#include <GL/gl.h>


typedef struct
{
  GLuint shader;
} shader_t;

shader_t *make_shader(GLenum shader_type, const char *file_name);
