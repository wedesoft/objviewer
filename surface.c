#include <gc.h>
#include "surface.h"


surface_t *make_surface(int max_array, int max_indices)
{
  surface_t *retval = GC_MALLOC(sizeof(surface_t));
  retval->n_array = 0;
  retval->array = GC_MALLOC_ATOMIC(max_array * sizeof(GLfloat));
  retval->n_indices = 0;
  retval->vertex_index = GC_MALLOC_ATOMIC(max_indices * sizeof(int));
  return retval;
}

void add_vertex(surface_t *surface, vertex_t vertex)
{
  surface->array[surface->n_array++] = vertex.x;
  surface->array[surface->n_array++] = vertex.y;
  surface->array[surface->n_array++] = vertex.z;
}

void add_normal(surface_t *surface, normal_t normal)
{
  surface->array[surface->n_array++] = normal.x;
  surface->array[surface->n_array++] = normal.y;
  surface->array[surface->n_array++] = normal.z;
}

int size_of_array(surface_t *surface)
{
  return surface->n_array * sizeof(GLfloat);
}
