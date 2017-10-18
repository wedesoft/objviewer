#include <GL/gl.h>
#include "object.h"
#include "test_object.h"
#include "test_helper.h"


static MunitResult test_clear_buffer(const MunitParameter params[], void *data)
{
  object_t *object = make_object(make_rgb(0.75f, 0.25f, 0.125f), 1);
  render(object);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("clear_buffer.ppm", width, height, pixels);
  munit_assert_int(pixels[0], ==, 191);
  munit_assert_int(pixels[1], ==,  64);
  munit_assert_int(pixels[2], ==,  32);
  return MUNIT_OK;
}

MunitTest test_object[] = {
  {"/clear_buffer", test_clear_buffer, test_setup_gl, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL           , NULL             , NULL         , NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
