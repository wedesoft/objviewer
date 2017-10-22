#include <math.h>
#include "fsim/projection.h"
#include "test_projection.h"
#include "test_helper.h"


static MunitResult test_horizontal_fov(const MunitParameter params[], void *data)
{
  munit_assert_double_equal(projection(320, 240, 1, 100, 90)[0], 1, 6);
  munit_assert_double_equal(projection(320, 240, 1, 100, 60)[0], sqrt(3.0f), 6);
  return MUNIT_OK;
}

static MunitResult test_vertical_fov(const MunitParameter params[], void *data)
{
  munit_assert_double_equal(projection(320, 320, 1, 100, 60)[5], sqrt(3.0f), 6);
  munit_assert_double_equal(projection(320, 240, 1, 100, 60)[5], 4.0f / sqrt(3.0f), 6);
  return MUNIT_OK;
}

static MunitResult test_perspective(const MunitParameter params[], void *data)
{
  munit_assert_float(projection(320, 240, 0.1f, 100, 60)[11], ==, -1.0f);
  munit_assert_float(projection(320, 240, 1, 3, 60)[10], ==, -2.0f);
  munit_assert_float(projection(320, 240, 1, 5, 60)[10], ==, -1.5f);
  munit_assert_float(projection(320, 240, 1, 3, 60)[14], ==, -3.0f);
  munit_assert_float(projection(320, 240, 1, 5, 60)[14], ==, -2.5f);
  return MUNIT_OK;
}

MunitTest test_projection[] = {
  {"/horizontal_fov", test_horizontal_fov, test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/vertical_fov"  , test_vertical_fov  , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/perspective"   , test_perspective   , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL             , NULL               , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
