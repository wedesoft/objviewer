#include <gc.h>
#include <GL/glew.h>
#include "program.h"
#include "shader.h"
#include "report_status.h"


static void finalize_program(GC_PTR obj, GC_PTR env)
{
  program_t *target = (program_t *)obj;
  if (target->program) {
    if (target->vertex_shader)
      glDetachShader(target->program, target->vertex_shader->shader);
    if (target->fragment_shader)
      glDetachShader(target->program, target->fragment_shader->shader);
    glDeleteProgram(target->program);
  };
}

program_t *make_program(const char *vertex_shader_file_name, const char *fragment_shader_file_name)
{
  program_t *retval = GC_MALLOC(sizeof(program_t));
  GC_register_finalizer(retval, finalize_program, 0, 0, 0);
  retval->vertex_shader = make_shader(GL_VERTEX_SHADER, vertex_shader_file_name);
  retval->fragment_shader = make_shader(GL_FRAGMENT_SHADER, fragment_shader_file_name);
  retval->program = glCreateProgram();
  retval->n_attributes = 0;
  retval->attribute_pointer = 0;
  if (retval->vertex_shader && retval->fragment_shader) {
    glAttachShader(retval->program, retval->vertex_shader->shader);
    glAttachShader(retval->program, retval->fragment_shader->shader);
    glLinkProgram(retval->program);
    if (!report_link_status(retval->program))
      retval = NULL;
  } else
    retval = NULL;
  return retval;
}
