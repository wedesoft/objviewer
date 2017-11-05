#include <gc.h>
#include "material.h"


material_t *make_material(void)
{
  material_t *result = GC_MALLOC(sizeof(material_t));
  result->ambient[0] = 0.0f;
  result->ambient[1] = 0.0f;
  result->ambient[2] = 0.0f;
  result->texture = NULL;
  return result;
}

void set_texture(material_t *material, image_t *texture)
{
  material->texture = texture;
}
