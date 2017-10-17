#include "normal.h"
#include "test_normal.h"


static MunitResult test_make_normal(const MunitParameter params[], void *data)
{
  normal_t normal = make_normal(0.36f, 0.48f, 0.8f);
  munit_assert_float(normal.x, ==, 0.36f);
  munit_assert_float(normal.y, ==, 0.48f);
  munit_assert_float(normal.z, ==, 0.80f);
  return MUNIT_OK;
}

MunitTest test_normal[] = {
  {"/make_normal", test_make_normal, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL          , NULL            , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
