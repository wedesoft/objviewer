#include "test_texture_coordinate.h"
#include "texture_coordinate.h"


static MunitResult test_make_texcoord(const MunitParameter params[], void *data)
{
  texture_coordinate_t coordinate = make_texture_coordinate(0.25f, 0.75f);
  munit_assert_float(coordinate.u, ==, 0.25f);
  munit_assert_float(coordinate.v, ==, 0.75f);
  return MUNIT_OK;
}

MunitTest test_texcoord[] = {
  {"/make_texcoord", test_make_texcoord, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL            , NULL              , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
