#include "fsim/parser.h"
#include "fsim/list.h"
#include "test_helper.h"


extern object_t *parse_string_core(const char *text);
extern list_t *parse_array;
extern list_t *parse_surface;


static MunitResult test_empty(const MunitParameter params[], void *data)
{
  munit_assert_ptr(parse_string(""), ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_object(const MunitParameter params[], void *data)
{
  munit_assert_ptr(parse_string("o test"), !=, NULL);
  return MUNIT_OK;
}

static MunitResult test_object_name(const MunitParameter params[], void *data)
{
  munit_assert_string_equal(parse_string("o test")->name, "test");
  return MUNIT_OK;
}

static MunitResult test_error(const MunitParameter params[], void *data)
{
  munit_assert_ptr(parse_string("o test\n?"), ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_no_newline_in_name(const MunitParameter params[], void *data)
{
  munit_assert_string_equal(parse_string("o test\n")->name, "test");
  return MUNIT_OK;
}

static MunitResult test_no_vertices(const MunitParameter params[], void *data)
{
  parse_string_core("");
  munit_assert_int(parse_array->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_read_vertex(const MunitParameter params[], void *data)
{
  parse_string_core("o test\nv 10 2.5 -3.25");
  munit_assert_int(parse_array->size, ==, 3);
  munit_assert_float(get_glfloat(parse_array)[0], ==, 10.0f);
  munit_assert_float(get_glfloat(parse_array)[1], ==,  2.5f);
  munit_assert_float(get_glfloat(parse_array)[2], ==, -3.25f);
  return MUNIT_OK;
}

static MunitResult test_two_vertices(const MunitParameter params[], void *data)
{
  parse_string_core("o test\nv 10 2.5 -3.25\nv .5 +1 -.25");
  munit_assert_int(parse_array->size, ==, 6);
  munit_assert_float(get_glfloat(parse_array)[3], ==,  0.5f);
  munit_assert_float(get_glfloat(parse_array)[4], ==,  1.0f);
  munit_assert_float(get_glfloat(parse_array)[5], ==, -0.25f);
  return MUNIT_OK;
}

static MunitResult test_cleanup_vertices(const MunitParameter params[], void *data)
{
  parse_string("o test\nv 10 2.5 3.25");
  munit_assert_ptr(parse_array, ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_no_surfaces(const MunitParameter params[], void *data)
{
  parse_string_core("");
  munit_assert_int(parse_surface->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_start_surface(const MunitParameter params[], void *data)
{
  parse_string_core("o test\ns off");
  munit_assert_int(parse_surface->size, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_two_surfaces(const MunitParameter params[], void *data)
{
  parse_string_core("o test\ns off\ns off");
  munit_assert_int(parse_surface->size, ==, 2);
  return MUNIT_OK;
}

static MunitResult test_cleanup_surfaces(const MunitParameter params[], void *data)
{
  parse_string("o test");
  munit_assert_ptr(parse_surface, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_surface_point(const MunitParameter params[], void *data)
{
  parse_string_core("o test\nv 1 2 3\nv 4 5 6\ns off\nf 1 2 3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->vertex_index->size, ==, 3);
  return MUNIT_OK;
}

MunitTest test_parser[] = {
  {"/empty"             , test_empty             , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/object"            , test_object            , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/object_name"       , test_object_name       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/error"             , test_error             , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_newline_in_name", test_no_newline_in_name, test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_vertices"       , test_no_vertices       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/read_vertex"       , test_read_vertex       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/two_vertices"      , test_two_vertices      , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/cleanup_vertices"  , test_cleanup_vertices  , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_surfaces"       , test_no_surfaces       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/start_surface"     , test_start_surface     , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/two_surfaces"      , test_two_surfaces      , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/cleanup_surfaces"  , test_cleanup_surfaces  , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/surface_point"     , test_surface_point     , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                 , NULL                   , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
