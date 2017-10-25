#include <gc.h>
#include <GL/glew.h>
#include "vertex_array_object.h"


static void finalize_vertex_array_object(GC_PTR obj, GC_PTR env)
{
  vertex_array_object_t *target = (vertex_array_object_t *)obj;
  glBindVertexArray(target->vertex_array_object);
  int i;
  for (i=0; i<target->program->n_attributes; i++)
    glDisableVertexAttribArray(i);
  if (target->n_textures > 0) {
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

vertex_array_object_t *make_vertex_array_object(program_t *program, surface_t *surface, int max_textures)
{
  vertex_array_object_t *retval = GC_MALLOC_ATOMIC(sizeof(vertex_array_object_t));
  GC_register_finalizer(retval, finalize_vertex_array_object, 0, 0, 0);
  retval->n_indices = surface->vertex_index.size;
  retval->program = program;
  retval->n_textures = 0;
  retval->texture = GC_MALLOC(max_textures * sizeof(texture_t *));
  glGenVertexArrays(1, &retval->vertex_array_object);
  glBindVertexArray(retval->vertex_array_object);
  glGenBuffers(1, &retval->vertex_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, retval->vertex_buffer_object);
  glBufferData(GL_ARRAY_BUFFER, size_of_array(surface), surface->array.element, GL_STATIC_DRAW);
  glGenBuffers(1, &retval->element_buffer_object);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval->element_buffer_object);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices(surface), surface->vertex_index.element, GL_STATIC_DRAW);
  return retval;
}

void setup_vertex_attribute_pointer(vertex_array_object_t *vertex_array_object, const char *attribute, int size, int stride)
{
  glBindVertexArray(vertex_array_object->vertex_array_object);
  program_t *program = vertex_array_object->program;
  GLuint index = glGetAttribLocation(program->program, attribute);
  glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)program->attribute_pointer);
  glEnableVertexAttribArray(program->n_attributes);
  program->n_attributes += 1;
  program->attribute_pointer += sizeof(float) * size;
}

void add_texture(vertex_array_object_t *vertex_array_object, program_t *program, texture_t *texture, image_t *image)
{
  vertex_array_object->texture[vertex_array_object->n_textures++] = texture;
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->texture);
  glUniform1i(glGetAttribLocation(program->program, texture->name), 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image->data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
