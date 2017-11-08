#include <gc.h>
#include <GL/glew.h>
#include "vertex_array_object.h"


static void finalize_vertex_array_object(GC_PTR obj, GC_PTR env)
{
  vertex_array_object_t *target = (vertex_array_object_t *)obj;
  glBindVertexArray(target->vertex_array_object);
  if (target->texture->size) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
  };
  glBindVertexArray(target->vertex_array_object);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &target->element_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &target->vertex_buffer_object);
  glBindVertexArray(0);
  glDeleteBuffers(1, &target->vertex_array_object);
}

void setup_vertex_attribute_pointers(vertex_array_object_t *vertex_array_object, int stride)
{
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, stride);
  if (stride == 5 || stride == 8)
    setup_vertex_attribute_pointer(vertex_array_object, "texcoord", 2, stride);
  if (stride == 6 || stride == 8)
    setup_vertex_attribute_pointer(vertex_array_object, "vector", 3, stride);
}

vertex_array_object_t *make_vertex_array_object(program_t *program, surface_t *surface)
{
  vertex_array_object_t *retval = GC_MALLOC_ATOMIC(sizeof(vertex_array_object_t));
  GC_register_finalizer(retval, finalize_vertex_array_object, 0, 0, 0);
  retval->n_indices = surface->vertex_index->size;
  retval->program = program;
  retval->n_attributes = 0;
  retval->attribute_pointer = 0;
  retval->texture = make_list();
  glGenVertexArrays(1, &retval->vertex_array_object);
  glBindVertexArray(retval->vertex_array_object);
  glGenBuffers(1, &retval->vertex_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, retval->vertex_buffer_object);
  glBufferData(GL_ARRAY_BUFFER, size_of_array(surface), surface->array->element, GL_STATIC_DRAW);
  glGenBuffers(1, &retval->element_buffer_object);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval->element_buffer_object);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices(surface), surface->vertex_index->element, GL_STATIC_DRAW);
  setup_vertex_attribute_pointers(retval, surface->stride);
  retval->material = surface->material;
  if (surface->material) {
    if (surface->material->texture)
      add_texture(retval, make_texture("tex"), surface->material->texture);
  };
  return retval;
}

list_t *make_vertex_array_object_list(program_t *program, object_t *object)
{
  list_t *result = make_list();
  int i;
  for (i=0; i<object->surface->size; i++)
    append_pointer(result, make_vertex_array_object(program, get_pointer(object->surface)[i]));
  return result;
}

void setup_vertex_attribute_pointer(vertex_array_object_t *vertex_array_object, const char *attribute, int size, int stride)
{
  glBindVertexArray(vertex_array_object->vertex_array_object);
  program_t *program = vertex_array_object->program;
  GLuint index = glGetAttribLocation(program->program, attribute);
  glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)vertex_array_object->attribute_pointer);
  glEnableVertexAttribArray(vertex_array_object->n_attributes);
  vertex_array_object->n_attributes += 1;
  vertex_array_object->attribute_pointer += sizeof(float) * size;
}

void add_texture(vertex_array_object_t *vertex_array_object, texture_t *texture, image_t *image)
{
  append_pointer(vertex_array_object->texture, texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->texture);
  glUniform1i(glGetAttribLocation(vertex_array_object->program->program, texture->name), 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image->data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void draw_elements(vertex_array_object_t *vertex_array_object)
{
  program_t *program = vertex_array_object->program;
  glUseProgram(program->program);
  if (vertex_array_object->material) {
    material_t *material = vertex_array_object->material;
    glUniform3fv(glGetUniformLocation(program->program, "ambient"), 1, &material->ambient[0]);
    glUniform3fv(glGetUniformLocation(program->program, "diffuse"), 1, &material->diffuse[0]);
    glUniform3fv(glGetUniformLocation(program->program, "specular"), 1, &material->specular[0]);
    glUniform1f(glGetUniformLocation(program->program, "specular_exponent"), material->specular_exponent);
  };
  if (vertex_array_object->material && vertex_array_object->material->texture) {
    texture_t *texture = get_pointer(vertex_array_object->texture)[0];
    glBindTexture(GL_TEXTURE_2D, texture->texture);
  };
  glBindVertexArray(vertex_array_object->vertex_array_object);
  glDrawElements(GL_TRIANGLES, vertex_array_object->n_indices, GL_UNSIGNED_INT, (void *)0);
}

void render(list_t *vertex_array_object)
{
  int i;
  for (i=0; i<vertex_array_object->size; i++)
    draw_elements(get_pointer(vertex_array_object)[i]);
}
