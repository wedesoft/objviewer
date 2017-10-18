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
  return MUNIT_OK;
}

static MunitResult test_add_two_vertices(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface(9, 3);
  add_vertex(surface, make_vertex(2.5f, 3.5f, 5.5f));
  add_vertex(surface, make_vertex(1.5f, 4.5f, 7.5f));
  munit_assert_float(surface->array[3], ==, 1.5f);
  munit_assert_float(surface->array[4], ==, 4.5f);
  munit_assert_float(surface->array[5], ==, 7.5f);
  return MUNIT_OK;
}

static MunitResult test_add_normal(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface(18, 3);
  add_vertex(surface, make_vertex(2.5f, 3.5f, 5.5f));
  add_normal(surface, make_normal(0.36f, 0.48f, 0.8f));
  munit_assert_int(surface->n_array, ==, 6);
  munit_assert_float(surface->array[3], ==, 0.36f);
  munit_assert_float(surface->array[4], ==, 0.48f);
  munit_assert_float(surface->array[5], ==, 0.80f);
  return MUNIT_OK;
}

static MunitResult test_size_of_array(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface(9, 3);
  munit_assert_int(size_of_array(surface), ==, 0);
  add_vertex(surface, make_vertex(2.5f, 3.5f, 5.5f));
  munit_assert_int(size_of_array(surface), ==, sizeof(vertex_t));
  return MUNIT_OK;
}

MunitTest test_surface[] = {
  {"/empty_surface"   , test_empty_surface   , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_one_vertex"  , test_add_one_vertex  , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_two_vertices", test_add_two_vertices, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_normal"      , test_add_normal      , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL               , NULL                 , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
