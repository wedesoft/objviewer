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
  result->texture = NULL;
  return result;
}

void set_texture(material_t *material, image_t *texture)
{
  material->texture = texture;
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
