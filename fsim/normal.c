#include "normal.h"


normal_t make_normal(GLfloat x, GLfloat y, GLfloat z)
{
  normal_t retval;
  retval.x = x;
  retval.y = y;
  retval.z = z;
  return retval;
}
