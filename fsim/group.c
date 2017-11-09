#include <gc.h>
#include "group.h"


group_t *make_group(int stride)
{
  group_t *retval = GC_MALLOC(sizeof(group_t));
  retval->array = make_list();
  retval->vertex_index = make_list();
  retval->stride = stride;
  retval->material = NULL;
  return retval;
}

void add_vertex_data(group_t *group, int n, ...)
{
  va_list data;
  va_start(data, n);
  int i;
  for (i=0; i<n; i++)
    append_glfloat(group->array, va_arg(data, double));
}

int size_of_array(group_t *group)
{
  return group->array->size * sizeof(GLfloat);
}

int size_of_indices(group_t *group)
{
  return group->vertex_index->size * sizeof(GLuint);
}

void add_triangle(group_t *group, int index1, int index2, int index3)
{
  append_gluint(group->vertex_index, index1);
  append_gluint(group->vertex_index, index2);
  append_gluint(group->vertex_index, index3);
}

void extend_triangle(group_t *group, int index)
{
  int n = group->vertex_index->size;
  int index1 = get_gluint(group->vertex_index)[n - 3];
  int index2 = get_gluint(group->vertex_index)[n - 1];
  add_triangle(group, index1, index2, index);
}

void use_material(group_t *group, material_t *material)
{
  group->material = material;
}
