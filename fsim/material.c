#include <gc.h>
#include "material.h"


material_t *make_material(void)
{
  return GC_MALLOC(sizeof(material_t));
}
