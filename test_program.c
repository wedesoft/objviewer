#include "test_program.h"
#include "test_helper.h"
#include "program.h"


static MunitResult test_no_vertex_shader(const MunitParameter params[], void *data)
{
  munit_assert_ptr(make_program("no-such-file.glsl", "fragment-blue.glsl"), ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_no_fragment_shader(const MunitParameter params[], void *data)
{
  munit_assert_ptr(make_program("vertex-identity.glsl", "no-such-file.glsl"), ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_compile_program(const MunitParameter params[], void *data)
{
  munit_assert_ptr(make_program("vertex-identity.glsl", "fragment-blue.glsl"), !=, NULL);
  return MUNIT_OK;
}

MunitTest test_program[] = {
  {"/no_vertex_shader"     , test_no_vertex_shader     , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_fragment_shader"   , test_no_fragment_shader   , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/compile_program"      , test_compile_program      , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                    , NULL                      , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
