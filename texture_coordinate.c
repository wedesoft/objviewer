#include "texture_coordinate.h"


texture_coordinate_t make_texture_coordinate(GLfloat u, GLfloat v)
{
  texture_coordinate_t retval;
  retval.u = u;
  retval.v = v;
  return retval;
}
