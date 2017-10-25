#include <GL/gl.h>
#include "fsim/list.h"
#include "test_list.h"
#include "test_helper.h"


static MunitResult test_zero_size(const MunitParameter params[], void *data)
{
  munit_assert_int(make_list().size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_append_gluint(const MunitParameter params[], void *data)
{
  list_t list = make_list();
  list_append_gluint(&list, 123);
  munit_assert_int(list.size, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_get_gluint(const MunitParameter params[], void *data)
{
  list_t list = make_list();
  list_append_gluint(&list, 123);
  munit_assert_int(get_gluint(&list)[0], ==, 123);
  return MUNIT_OK;
}

static MunitResult test_append_two(const MunitParameter params[], void *data)
{
  list_t list = make_list();
  list_append_gluint(&list, 235);
  list_append_gluint(&list, 357);
  munit_assert_int(list.size, ==, 2);
  return MUNIT_OK;
}

static MunitResult test_get_two(const MunitParameter params[], void *data)
{
  list_t list = make_list();
  list_append_gluint(&list, 235);
  list_append_gluint(&list, 357);
  munit_assert_int(get_gluint(&list)[0], ==, 235);
  munit_assert_int(get_gluint(&list)[1], ==, 357);
  return MUNIT_OK;
}

static MunitResult test_initial_storage(const MunitParameter params[], void *data)
{
  munit_assert_int(make_list().buffer_size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_allocation(const MunitParameter params[], void *data)
{
  list_t list = make_list();
  list_append_gluint(&list, 235);
  munit_assert_int(list.buffer_size, ==, sizeof(GLuint));
  return MUNIT_OK;
}

static MunitResult test_reallocation(const MunitParameter params[], void *data)
{
  list_t list = make_list();
  list_append_gluint(&list, 235);
  list_append_gluint(&list, 357);
  munit_assert_int(list.buffer_size, ==, 2 * sizeof(GLuint));
  return MUNIT_OK;
}

static MunitResult test_double_size(const MunitParameter params[], void *data)
{
  list_t list = make_list();
  list_append_gluint(&list, 235);
  list_append_gluint(&list, 357);
  list_append_gluint(&list, 5711);
  munit_assert_int(list.buffer_size, ==, 4 * sizeof(GLuint));
  return MUNIT_OK;
}

MunitTest test_list[] = {
  {"/zero_size"      , test_zero_size      , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/append_gluint"  , test_append_gluint  , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/get_gluint"     , test_get_gluint     , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/append_two"     , test_append_two     , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/get_two"        , test_get_two        , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/initial_storage", test_initial_storage, test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/allocation"     , test_allocation     , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/reallocation"   , test_reallocation   , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/double_size"    , test_double_size    , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL              , NULL                , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
