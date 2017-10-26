#include <gc.h>
#include "surface.h"


surface_t *make_surface(void)
{
  surface_t *retval = GC_MALLOC(sizeof(surface_t));
  retval->array = make_list();
  retval->vertex_index = make_list();
  return retval;
}

void add_vertex(surface_t *surface, GLfloat x, GLfloat y, GLfloat z)
{
  append_glfloat(&surface->array, x);
  append_glfloat(&surface->array, y);
  append_glfloat(&surface->array, z);
}

void add_normal(surface_t *surface, GLfloat x, GLfloat y, GLfloat z)
{
  append_glfloat(&surface->array, x);
  append_glfloat(&surface->array, y);
  append_glfloat(&surface->array, z);
}

void add_texture_coordinate(surface_t *surface, texture_coordinate_t texture_coordinate)
{
  append_glfloat(&surface->array, texture_coordinate.u);
  append_glfloat(&surface->array, texture_coordinate.v);
}

int size_of_array(surface_t *surface)
{
  return surface->array.size * sizeof(GLfloat);
}

int size_of_indices(surface_t *surface)
{
  return surface->vertex_index.size * sizeof(GLuint);
}

void add_polygon(surface_t *surface, int n, ...)
{
  va_list index;
  va_start(index, n);
  int i;
  for (i=0; i<3; i++)
    append_gluint(&surface->vertex_index, va_arg(index, int));
  for (i=3; i<n; i++) {
    int n = surface->vertex_index.size;
    int index1 = get_gluint(&surface->vertex_index)[n - 3];
    int index2 = get_gluint(&surface->vertex_index)[n - 1];
    add_polygon(surface, 3, index1, index2, va_arg(index, int));
  };
}
