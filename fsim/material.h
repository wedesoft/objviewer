#pragma once
#include <GL/gl.h>


typedef struct
{
  GLfloat ambient[3];
} material_t;

material_t* make_material(void);
