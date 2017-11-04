
#include "fsim/hash.h"
#include "test_hash.h"
#include "test_helper.h"


static MunitResult test_default(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  munit_assert_float(material->ambient[0], ==, 0.0f);
  munit_assert_float(material->ambient[1], ==, 0.0f);
  munit_assert_float(material->ambient[2], ==, 0.0f);
  return MUNIT_OK;
}

MunitTest test_material[] = {
  {"/default"          , test_default          , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                , NULL                  , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
