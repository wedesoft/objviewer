#include <gc.h>
#include <GL/glew.h>
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
  result->diffuse_texture = NULL;
  result->specular_texture = NULL;
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

static texture_t *setup_texture(const char *name, image_t *image)
{
  if (!image) return NULL;
  texture_t *result = make_texture(name);
  glBindTexture(GL_TEXTURE_2D, result->texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image->data);
  // http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
    GLfloat max_anisotropy;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
  };
  glGenerateMipmap(GL_TEXTURE_2D);
  return result;
}

void set_diffuse_texture(material_t *material, image_t *image)
{
  material->diffuse_texture = setup_texture("map_Kd", image);
}

void set_specular_texture(material_t *material, image_t *image)
{
  material->specular_texture = setup_texture("map_Ks", image);
}
