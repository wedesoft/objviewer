#include "fsim/parser.h"
#include "fsim/list.h"
#include "test_helper.h"


extern object_t *parse_string_core(const char *text);
extern list_t parse_array;


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

static MunitResult test_read_vertex(const MunitParameter params[], void *data)
{
  parse_string_core("o test\nv 10 2.5 3.25");
  munit_assert_int(parse_array.size, ==, 3);
  munit_assert_float(get_glfloat(&parse_array)[0], ==, 10.0f);
  munit_assert_float(get_glfloat(&parse_array)[1], ==, 2.5f);
  munit_assert_float(get_glfloat(&parse_array)[2], ==, 3.25f);
  return MUNIT_OK;
}

MunitTest test_parser[] = {
  {"/empty"             , test_empty             , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/object"            , test_object            , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/object_name"       , test_object_name       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/error"             , test_error             , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_newline_in_name", test_no_newline_in_name, test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/read_vertex"       , test_read_vertex       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                 , NULL                   , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
