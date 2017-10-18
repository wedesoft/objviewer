#include <GL/gl.h>
#include "object.h"
#include "program.h"
#include "test_object.h"
#include "test_helper.h"


static MunitResult test_clear_buffer(const MunitParameter params[], void *data)
{
  object_t *object = make_object(make_rgb(0.75f, 0.25f, 0.125f), 1);
  render(object);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("clear_buffer.ppm", width, height, pixels);
  munit_assert_int(pixels[0], ==, 191);
  munit_assert_int(pixels[1], ==,  64);
  munit_assert_int(pixels[2], ==,  32);
  return MUNIT_OK;
}

static MunitResult test_empty_object(const MunitParameter params[], void *data)
{
  object_t *object = make_object(make_rgb(0, 0, 0), 1);
  munit_assert_int(object->n_vertex_array_objects, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_add_vertex_array_object(const MunitParameter params[], void *data)
{
  object_t *object = make_object(make_rgb(0, 0, 0), 1);
  program_t *program = make_program("vertex-identity.glsl", "fragment-blue.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, make_surface(9, 3), 1);
  object_t *retval = add_vertex_array_object(object, vertex_array_object);
  munit_assert_int(object->n_vertex_array_objects, ==, 1);
  munit_assert_ptr(object->vertex_array_object[0], ==, vertex_array_object);
  munit_assert_ptr(retval, ==, object);
  return MUNIT_OK;
}

MunitTest test_object[] = {
  {"/clear_buffer"           , test_clear_buffer           , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/empty_object"           , test_empty_object           , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_vertex_array_object", test_add_vertex_array_object, test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                      , NULL                        , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
