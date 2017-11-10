#pragma once
#include <GL/gl.h>
#include "texture.h"
#include "image.h"


typedef struct
{
  GLfloat ambient[3];
  GLfloat diffuse[3];
  GLfloat specular[3];
  GLfloat specular_exponent;
  GLfloat optical_density;
  GLfloat disolve;
  texture_t *diffuse_texture;
} material_t;

material_t* make_material(void);

void set_ambient(material_t *material, GLfloat red, GLfloat green, GLfloat blue);

void set_diffuse(material_t *material, GLfloat red, GLfloat green, GLfloat blue);

void set_specular(material_t *material, GLfloat red, GLfloat green, GLfloat blue);

void set_specular_exponent(material_t *material, GLfloat specular_exponent);

void set_optical_density(material_t *material, GLfloat optical_density);

void set_disolve(material_t *material, GLfloat disolve);

void set_diffuse_texture(material_t *material, image_t *texture);
