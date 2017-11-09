#include <GL/gl.h>
#include "fsim/object.h"
#include "fsim/program.h"
#include "fsim/vertex_array_object.h"
#include "test_object.h"
#include "test_helper.h"


static MunitResult test_empty_object(const MunitParameter params[], void *data)
{
  object_t *object = make_object("test");
  munit_assert_int(object->group->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_object_name(const MunitParameter params[], void *data)
{
  object_t *object = make_object("test");
  munit_assert_string_equal(object->name, "test");
  return MUNIT_OK;
}

static MunitResult test_copy_name(const MunitParameter params[], void *data)
{
  char test[2] = "x";
  object_t *object = make_object(test);
  test[0] = 'y';
  munit_assert_string_equal(object->name, "x");
  return MUNIT_OK;
}

static MunitResult test_add_group(const MunitParameter params[], void *data)
{
  object_t *object = make_object("test");
  group_t *group = make_group(3);
  object_t *retval = add_group(object, group);
  munit_assert_int(object->group->size, ==, 1);
  munit_assert_ptr(get_pointer(object->group)[0], ==, group);
  munit_assert_ptr(retval, ==, object);
  return MUNIT_OK;
}

MunitTest test_object[] = {
  {"/empty_object", test_empty_object, test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/object_name" , test_object_name , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/copy_name"   , test_copy_name   , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_group"   , test_add_group   , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL           , NULL             , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
