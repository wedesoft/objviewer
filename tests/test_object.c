#include <GL/gl.h>
#include "fsim/object.h"
#include "fsim/program.h"
#include "fsim/vertex_array_object.h"
#include "test_object.h"
#include "test_helper.h"


static MunitResult test_empty_object(const MunitParameter params[], void *data)
{
  object_t *object = make_object("test");
  munit_assert_int(object->surface->size, ==, 0);
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

static MunitResult test_add_surface(const MunitParameter params[], void *data)
{
  object_t *object = make_object("test");
  surface_t *surface = make_surface();
  object_t *retval = add_surface(object, surface);
  munit_assert_int(object->surface->size, ==, 1);
  munit_assert_ptr(get_pointer(object->surface)[0], ==, surface);
  munit_assert_ptr(retval, ==, object);
  return MUNIT_OK;
}

MunitTest test_object[] = {
  {"/empty_object", test_empty_object, test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/object_name" , test_object_name , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/copy_name"   , test_copy_name   , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_surface" , test_add_surface , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL           , NULL             , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
