#include <GL/glew.h>
#include <gc.h>
#include "object.h"


object_t *make_object(rgb_t background_color)
{
  object_t *retval = GC_MALLOC(sizeof(object_t));
  retval->background_color = background_color;
  retval->vertex_array_object = make_list();
  return retval;
}

object_t *add_vertex_array_object(object_t *object, vertex_array_object_t *vertex_array_object)
{
  append_pointer(&object->vertex_array_object, vertex_array_object);
  return object;
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int i;
  for (i=0; i<object->vertex_array_object.size; i++)
    draw_elements(get_pointer(&object->vertex_array_object)[i]);
}
