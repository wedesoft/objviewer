#include <gc.h>
#include "texture.h"


static void finalize_texture(GC_PTR obj, GC_PTR env)
{
  texture_t *target = (texture_t *)obj;
  glDeleteTextures(1, &target->texture);
}

texture_t *make_texture(const char *name)
{
  texture_t *retval = GC_MALLOC_ATOMIC(sizeof(texture_t));
  GC_register_finalizer(retval, finalize_texture, 0, 0, 0);
  retval->name = name;
  glGenTextures(1, &retval->texture);
  return retval;
}
