#include "fsim/texture.h"
#include "test_texture.h"


static MunitResult test_make_texture(const MunitParameter params[], void *data)
{
  texture_t *texture = make_texture("tex");
  munit_assert_ptr(texture, !=, NULL);
  munit_assert_string_equal(texture->name, "tex");
  return MUNIT_OK;
}

MunitTest test_texture[] = {
  {"/make_texture", test_make_texture, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL           , NULL             , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
