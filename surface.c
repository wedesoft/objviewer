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
