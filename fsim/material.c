#include <gc.h>
#include "material.h"


material_t *make_material(void)
{
  material_t *result = GC_MALLOC(sizeof(material_t));
  result->ambient[0] = 0.0f;
  result->ambient[1] = 0.0f;
  result->ambient[2] = 0.0f;
  result->diffuse[0] = 0.0f;
  result->diffuse[1] = 0.0f;
  result->diffuse[2] = 0.0f;
  result->specular[0] = 0.0f;
  result->specular[1] = 0.0f;
  result->specular[2] = 0.0f;
  result->specular_exponent = 1.0f;
  result->optical_density = 1.0f;
  result->disolve = 1.0f;
  result->texture = NULL;
  return result;
}

void set_ambient(material_t *material, GLfloat red, GLfloat green, GLfloat blue)
{
  material->ambient[0] = red;
  material->ambient[1] = green;
  material->ambient[2] = blue;
}

void set_diffuse(material_t *material, GLfloat red, GLfloat green, GLfloat blue)
{
  material->diffuse[0] = red;
  material->diffuse[1] = green;
  material->diffuse[2] = blue;
}

void set_specular(material_t *material, GLfloat red, GLfloat green, GLfloat blue)
{
  material->specular[0] = red;
  material->specular[1] = green;
  material->specular[2] = blue;
}

void set_specular_exponent(material_t *material, GLfloat specular_exponent)
{
  material->specular_exponent = specular_exponent;
}

void set_optical_density(material_t *material, GLfloat optical_density)
{
  material->optical_density = optical_density;
}

void set_disolve(material_t *material, GLfloat disolve)
{
  material->disolve = disolve;
}

void set_texture(material_t *material, image_t *image)
{
  if (!image) return;
  material->texture = make_texture("tex");
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, material->texture->texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image->data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
