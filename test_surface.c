#include "surface.h"
#include "test_surface.h"


static MunitResult test_empty_surface(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface(9, 3);
  munit_assert_int(surface->n_array, ==, 0);
  return MUNIT_OK;
}

MunitTest test_surface[] = {
  {"/empty_surface", test_empty_surface, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL            , NULL              , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
