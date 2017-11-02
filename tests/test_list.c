#include <GL/gl.h>
#include "fsim/list.h"
#include "test_list.h"
#include "test_helper.h"


static MunitResult test_zero_size(const MunitParameter params[], void *data)
{
  munit_assert_int(make_list()->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_append_gluint(const MunitParameter params[], void *data)
{
  list_t *list = make_list();
  append_gluint(list, 123);
  munit_assert_int(list->size, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_get_gluint(const MunitParameter params[], void *data)
{
  list_t *list = make_list();
  append_gluint(list, 123);
  munit_assert_int(get_gluint(list)[0], ==, 123);
  return MUNIT_OK;
}

static MunitResult test_append_two(const MunitParameter params[], void *data)
{
  list_t *list = make_list();
  append_gluint(list, 235);
  append_gluint(list, 357);
  munit_assert_int(list->size, ==, 2);
  return MUNIT_OK;
}

static MunitResult test_get_two(const MunitParameter params[], void *data)
{
  list_t *list = make_list();
  append_gluint(list, 235);
  append_gluint(list, 357);
  munit_assert_int(get_gluint(list)[0], ==, 235);
  munit_assert_int(get_gluint(list)[1], ==, 357);
  return MUNIT_OK;
}

static MunitResult test_initial_storage(const MunitParameter params[], void *data)
{
  munit_assert_int(make_list()->buffer_size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_allocation(const MunitParameter params[], void *data)
{
  list_t *list = make_list();
  append_gluint(list, 235);
  munit_assert_int(list->buffer_size, ==, sizeof(GLuint));
  return MUNIT_OK;
}

static MunitResult test_reallocation(const MunitParameter params[], void *data)
{
  list_t *list = make_list();
  append_gluint(list, 235);
  append_gluint(list, 357);
  munit_assert_int(list->buffer_size, ==, 2 * sizeof(GLuint));
  return MUNIT_OK;
}

static MunitResult test_double_size(const MunitParameter params[], void *data)
{
  list_t *list = make_list();
  append_gluint(list, 235);
  append_gluint(list, 357);
  append_gluint(list, 5711);
  munit_assert_int(list->buffer_size, ==, 4 * sizeof(GLuint));
  return MUNIT_OK;
}

static MunitResult test_append_glfloat(const MunitParameter params[], void *data)
{
  list_t *list = make_list();
  append_glfloat(list, 2.5f);
  munit_assert_int(list->size, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_get_glfloat(const MunitParameter params[], void *data)
{
  list_t *list = make_list();
  append_glfloat(list, 7.5f);
  munit_assert_float(get_glfloat(list)[0], ==, 7.5f);
  return MUNIT_OK;
}

static MunitResult test_append_pointer(const MunitParameter params[], void *data)
{
  list_t *list = make_list();
  append_pointer(list, NULL);
  munit_assert_int(list->size, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_get_pointer(const MunitParameter params[], void *data)
{
  char test = 42;
  list_t *list = make_list();
  append_pointer(list, &test);
  munit_assert_ptr(get_pointer(list)[0], ==, &test);
  return MUNIT_OK;
}

MunitTest test_list[] = {
  {"/zero_size"      , test_zero_size      , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/append_gluint"  , test_append_gluint  , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/get_gluint"     , test_get_gluint     , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/append_two"     , test_append_two     , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/get_two"        , test_get_two        , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/initial_storage", test_initial_storage, test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/allocation"     , test_allocation     , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/reallocation"   , test_reallocation   , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/double_size"    , test_double_size    , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/append_glfloat" , test_append_glfloat , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/get_glfloat"    , test_get_glfloat    , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/append_pointer" , test_append_pointer , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/get_pointer"    , test_get_pointer    , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL              , NULL                , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
