
#include "fsim/hash.h"
#include "test_hash.h"
#include "test_helper.h"


static MunitResult test_default(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  munit_assert_float(material->ambient[0], ==, 0.0f);
  munit_assert_float(material->ambient[1], ==, 0.0f);
  munit_assert_float(material->ambient[2], ==, 0.0f);
  munit_assert_ptr(material->texture, ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_set_texture(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  image_t *texture = read_image("colors.png");
  set_texture(material, texture);
  munit_assert_ptr(material->texture, ==, texture);
  return MUNIT_OK;
}

MunitTest test_material[] = {
  {"/default"          , test_default          , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/set_texture"      , test_set_texture      , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                , NULL                  , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
