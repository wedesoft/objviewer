#include "surface.h"
#include "test_surface.h"


static MunitResult test_empty_surface(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface(9, 3);
  munit_assert_int(surface->n_array, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_add_one_vertex(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface(9, 3);
  add_vertex(surface, make_vertex(2.5f, 3.5f, 5.5f));
  munit_assert_int(surface->n_array, ==, 3);
  munit_assert_float(surface->array[0], ==, 2.5f);
  munit_assert_float(surface->array[1], ==, 3.5f);
  munit_assert_float(surface->array[2], ==, 5.5f);
}

MunitTest test_surface[] = {
  {"/empty_surface" , test_empty_surface , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_one_vertex", test_add_one_vertex, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL             , NULL               , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
