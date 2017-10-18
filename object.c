#define GLEW_STATIC
#include <GL/glew.h>
#include <gc.h>
#include "object.h"


object_t *make_object(rgb_t background_color, int max_vertex_array_objects)
{
  object_t *retval = GC_MALLOC(sizeof(object_t));
  retval->background_color = background_color;
  retval->n_vertex_array_objects = 0;
  retval->vertex_array_object = GC_MALLOC(max_vertex_array_objects * sizeof(vertex_array_object_t *));
  return retval;
}

void draw_elements(vertex_array_object_t *vertex_array_object)
{
  glUseProgram(vertex_array_object->program->program);
  glBindVertexArray(vertex_array_object->vertex_array_object);
  glDrawElements(GL_TRIANGLES, vertex_array_object->n_indices, GL_UNSIGNED_INT, (void *)0);
}

void render(object_t *object)
{
  rgb_t c = object->background_color;
  glClearColor(c.red, c.green, c.blue, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  int i;
  for (i=0; i<object->n_vertex_array_objects; i++)
    draw_elements(object->vertex_array_object[i]);
}
