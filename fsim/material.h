#pragma once
#include <GL/gl.h>
#include "image.h"


typedef struct
{
  GLfloat ambient[3];
  image_t *texture;
} material_t;

material_t* make_material(void);
