#include "test_rgb.h"
#include "rgb.h"


static MunitResult test_make_rgb(const MunitParameter params[], void *data)
{
  rgb_t color = make_rgb(0.50f, 0.75f, 0.25f);
  munit_assert_float(color.red  , ==, 0.50f);
  munit_assert_float(color.green, ==, 0.75f);
  munit_assert_float(color.blue , ==, 0.25f);
  return MUNIT_OK;
}

MunitTest test_rgb[] = {
  {"/make_rgb", test_make_rgb, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL       , NULL         , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
