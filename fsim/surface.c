#include <gc.h>
#include "surface.h"


surface_t *make_surface(void)
{
  surface_t *retval = GC_MALLOC(sizeof(surface_t));
  retval->array = make_list();
  retval->vertex_index = make_list();
  return retval;
}

void add_vertex(surface_t *surface, vertex_t vertex)
{
  append_glfloat(&surface->array, vertex.x);
  append_glfloat(&surface->array, vertex.y);
  append_glfloat(&surface->array, vertex.z);
}

void add_normal(surface_t *surface, normal_t normal)
{
  append_glfloat(&surface->array, normal.x);
  append_glfloat(&surface->array, normal.y);
  append_glfloat(&surface->array, normal.z);
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

void build_facet(surface_t *surface, int number, int index)
{
  if (number < 3)
    append_gluint(&surface->vertex_index, index);
  else {
    int n = surface->vertex_index.size;
    build_facet(surface, 0, get_gluint(&surface->vertex_index)[n - 3]);
    build_facet(surface, 1, get_gluint(&surface->vertex_index)[n - 1]);
    build_facet(surface, 2, index);
  };
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
  for (i=0; i<n; i++)
    build_facet(surface, i, va_arg(index, int));
}
