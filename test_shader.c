#include "test_shader.h"
#include "test_helper.h"
#include "shader.h"


static MunitResult test_shader_file_not_found(const MunitParameter params[], void *data)
{
  munit_assert_ptr(make_shader(GL_VERTEX_SHADER, "no-such-file.glsl"), ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_compile_shader(const MunitParameter params[], void *data)
{
  munit_assert_ptr(make_shader(GL_VERTEX_SHADER, "vertex-identity.glsl"), !=, NULL);
  return MUNIT_OK;
}

MunitTest test_shader[] = {
  {"/shader_file_not_found", test_shader_file_not_found, test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/compile_shader"       , test_compile_shader       , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                    , NULL                      , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
