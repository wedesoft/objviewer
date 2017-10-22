#include <stdio.h>
#include <gc.h>
#include <GL/glew.h>
#include "report_status.h"


int report_status(const char *text, GLuint context, GLuint status)
{
  GLint result = GL_FALSE;
  GLint length = 0;
  glGetShaderiv(context, status, &result);
  if (result == GL_FALSE) {
    glGetShaderiv(context, GL_INFO_LOG_LENGTH, &length);
    char *info = GC_MALLOC_ATOMIC(length + 1);
    info[0] = 0;
    if (status == GL_COMPILE_STATUS)
      glGetShaderInfoLog(context, length, NULL, info);
    else
      glGetProgramInfoLog(context, length, NULL, info);
    if (info[0])
      fprintf(stderr, "%s: %s\n", text, info);
    else
      result = GL_TRUE;
  };
  return result;
}

int report_compile_status(const char *file_name, GLuint context)
{
  return report_status(file_name, context, GL_COMPILE_STATUS);
}

int report_link_status(GLuint context)
{
  return report_status("link shader program", context, GL_LINK_STATUS);
}

