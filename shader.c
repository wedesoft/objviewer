#include <stdio.h>
#include <sys/stat.h>
#include <gc.h>
#include <GL/glew.h>
#include "shader.h"
#include "report_status.h"


static void finalize_shader(GC_PTR obj, GC_PTR env)
{
  shader_t *target = (shader_t *)obj;
  if (target->shader)
    glDeleteShader(target->shader);
}

shader_t *make_shader(GLenum shader_type, const char *file_name)
{
  shader_t *retval = GC_MALLOC_ATOMIC(sizeof(shader_t));
  GC_register_finalizer(retval, finalize_shader, 0, 0, 0);
  retval->shader = 0;
  FILE *f = fopen(file_name, "r");
  if (f) {
    struct stat st;
    stat(file_name, &st);
    char *source = GC_MALLOC_ATOMIC(st.st_size + 1);
    fread(source, st.st_size, 1, f);
    source[st.st_size] = '\0';
    fclose(f);
    retval->shader = glCreateShader(shader_type);
    const GLchar *shader_source = source;
    glShaderSource(retval->shader, 1, &shader_source, NULL);
    glCompileShader(retval->shader);
    if (!report_compile_status(file_name, retval->shader))
      retval = NULL;
  } else
    retval = NULL;
  return retval;
}
