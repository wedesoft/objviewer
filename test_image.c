#include "test_image.h"
#include "test_helper.h"
#include "image.h"


static MunitResult test_image_size(const MunitParameter params[], void *data)
{
  image_t *image = read_image("colors.png");
  munit_assert_int(image->width , ==, 64);
  munit_assert_int(image->height, ==, 64);
  return MUNIT_OK;
}

static MunitResult test_load_image_data(const MunitParameter params[], void *data)
{
  image_t *image = read_image("colors.png");
  munit_assert_int(image->data[0], ==,   0);
  munit_assert_int(image->data[1], ==,   0);
  munit_assert_int(image->data[2], ==, 255);
  return MUNIT_OK;
}

static MunitResult test_image_not_found(const MunitParameter params[], void *data)
{
  munit_assert_ptr(read_image("nosuchfile.png"), ==, NULL);
  return MUNIT_OK;
}

MunitTest test_image[] = {
  {"/image_size"     , test_image_size     , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/load_image_data", test_load_image_data, test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/image_not_found", test_image_not_found, test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL              , NULL                , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
