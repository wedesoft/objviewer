#pragma once
#include <GL/gl.h>
#include "image.h"


typedef struct
{
  GLfloat ambient[3];
  GLfloat diffuse[3];
  image_t *texture;
} material_t;

material_t* make_material(void);

void set_ambient(material_t *material, GLfloat red, GLfloat green, GLfloat blue);

void set_diffuse(material_t *material, GLfloat red, GLfloat green, GLfloat blue);

void set_texture(material_t *material, image_t *texture);
