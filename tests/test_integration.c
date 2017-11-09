#include "test_integration.h"
#include "test_helper.h"
#include "fsim/object.h"
#include "fsim/parser.h"
#include "fsim/program.h"
#include "fsim/projection.h"
#include "fsim/vertex_array_object.h"


static MunitResult test_draw_triangle(const MunitParameter params[], void *data)
{
  object_t *object =
    parse_string("o draw triangle\n"
                 "v  0.5  0.5 0\n"
                 "v -0.5  0.5 0\n"
                 "v -0.5 -0.5 0\n"
                 "g triangle\n"
                 "f 1 2 3");
  program_t *program = make_program("vertex-identity.glsl", "fragment-blue.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 1, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("draw_triangle.ppm", width, height, pixels);
  munit_assert_int(pixels[0], ==,   0);
  munit_assert_int(pixels[1], ==, 255);
  munit_assert_int(pixels[2], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 0], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 2], ==, 255);
  return MUNIT_OK;
}

static MunitResult test_use_normal(const MunitParameter params[], void *data)
{
  object_t *object =
    parse_string("o use normals\n"
                 "v  0.5  0.5 0\n"
                 "v -0.5  0.5 0\n"
                 "v -0.5 -0.5 0\n"
                 "vn 0 0 1\n"
                 "vn 0 1 0\n"
                 "vn 1 0 0\n"
                 "g triangle with normals\n"
                 "f 1//1 2//2 3//3");
  program_t *program = make_program("vertex-normal-identity.glsl", "fragment-normal.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("use_normal.ppm", width, height, pixels);
  munit_assert_int(pixels[( 5 * 32 + 8 ) * 4 + 0], >=, 192);
  munit_assert_int(pixels[(14 * 32 + 8 ) * 4 + 0], < ,  64);
  munit_assert_int(pixels[(14 * 32 + 8 ) * 4 + 1], >=, 192);
  return MUNIT_OK;
}

static MunitResult test_draw_texturized_square(const MunitParameter params[], void *data)
{
  object_t *object =
    parse_string("newmtl colors\n"
                 "map_Kd colors.png\n"
                 "o texturized square\n"
                 "v -0.5 -0.5 0\n"
                 "v  0.5 -0.5 0\n"
                 "v -0.5  0.5 0\n"
                 "v  0.5  0.5 0\n"
                 "vt 0 0\n"
                 "vt 1 0\n"
                 "vt 0 1\n"
                 "vt 1 1\n"
                 "g texturized square\n"
                 "usemtl colors\n"
                 "f 1/1 2/2 4/4 3/3");
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-texture.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("draw_texturized_square.ppm", width, height, pixels);
  munit_assert_int(pixels[( 8 * 32 + 14 ) * 4 + 0], ==, 255);
  munit_assert_int(pixels[( 8 * 32 + 14 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[( 8 * 32 + 14 ) * 4 + 2], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 0], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 2], ==, 255);
  return MUNIT_OK;
}

static MunitResult test_perspective_triangle(const MunitParameter params[], void *data)
{
  object_t *object =
    parse_string("o perspective triangle\n"
                 "v  0.5  0.5 -1\n"
                 "v -0.5  0.5 -1\n"
                 "v -0.5 -0.5 -1\n"
                 "g triangle\n"
                 "f 1 2 3");
  program_t *program = make_program("vertex-projection.glsl", "fragment-blue.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  uniform_matrix(program, "projection", projection(width, height, 0.1, 2.0, 90.0));
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("project_triangle.ppm", width, height, pixels);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 0], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 2], ==, 255);
  return MUNIT_OK;
}

static MunitResult test_draw_two_textures(const MunitParameter params[], void *data)
{
  object_t *object =
    parse_string("newmtl colors\n"
                 "map_Kd colors.png\n"
                 "newmtl gray\n"
                 "map_Kd gray.png\n"
                 "o two textures\n"
                 "v -0.5 -0.5 0\n"
                 "v  0.5 -0.5 0\n"
                 "v -0.5  0.5 0\n"
                 "v  0.5  0.5 0\n"
                 "vt 0 0\n"
                 "vt 1 0\n"
                 "vt 0 1\n"
                 "vt 1 1\n"
                 "g first texturized triangle\n"
                 "usemtl colors\n"
                 "f 1/1 2/2 3/3\n"
                 "g second texturized triangle\n"
                 "usemtl gray\n"
                 "f 2/2 4/4 3/3");
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-texture.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("draw_two_textures.ppm", width, height, pixels);
  munit_assert_int(pixels[( 8 * 32 + 14 ) * 4 + 0], ==, 255);
  munit_assert_int(pixels[( 8 * 32 + 14 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[( 8 * 32 + 14 ) * 4 + 2], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 18 ) * 4 + 0], ==, 128);
  munit_assert_int(pixels[(12 * 32 + 18 ) * 4 + 1], ==, 128);
  munit_assert_int(pixels[(12 * 32 + 18 ) * 4 + 2], ==, 128);
  return MUNIT_OK;
}

static MunitResult test_ambient_color(const MunitParameter params[], void *data)
{
  object_t *object =
    parse_string("newmtl red\n"
                 "Ka 1 0 0\n"
                 "o ambient color\n"
                 "v -0.5 -0.5 0\n"
                 "v  0.5 -0.5 0\n"
                 "v -0.5  0.5 0\n"
                 "v  0.5  0.5 0\n"
                 "g red triangle\n"
                 "usemtl red\n"
                 "f 1 2 3");
  program_t *program = make_program("vertex-ambient.glsl", "fragment-ambient.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("ambient_color.ppm", width, height, pixels);
  munit_assert_int(pixels[(8 * 32 + 14) * 4 + 0], ==, 255);
  munit_assert_int(pixels[(8 * 32 + 14) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(8 * 32 + 14) * 4 + 2], ==,   0);
  return MUNIT_OK;
}

static MunitResult test_diffuse_color(const MunitParameter params[], void *data)
{
  object_t *object =
    parse_string("newmtl red\n"
                 "Kd 1 0 0\n"
                 "o diffuse color\n"
                 "v -0.5 -0.5 0\n"
                 "v  0.5 -0.5 0\n"
                 "v -0.5  0.5 0\n"
                 "v  0.5  0.5 0\n"
                 "g red triangle\n"
                 "usemtl red\n"
                 "f 1 2 3");
  program_t *program = make_program("vertex-diffuse.glsl", "fragment-diffuse.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("diffuse_color.ppm", width, height, pixels);
  munit_assert_int(pixels[(8 * 32 + 14) * 4 + 0], ==, 255);
  munit_assert_int(pixels[(8 * 32 + 14) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(8 * 32 + 14) * 4 + 2], ==,   0);
  return MUNIT_OK;
}

static MunitResult test_specular_color(const MunitParameter params[], void *data)
{
  object_t *object =
    parse_string("newmtl red\n"
                 "Ks 0.5 0 0\n"
                 "Ns 2.0\n"
                 "o specular color\n"
                 "v -0.5 -0.5 0\n"
                 "v  0.5 -0.5 0\n"
                 "v -0.5  0.5 0\n"
                 "v  0.5  0.5 0\n"
                 "g red triangle\n"
                 "usemtl red\n"
                 "f 1 2 3");
  program_t *program = make_program("vertex-specular.glsl", "fragment-specular.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("specular_color.ppm", width, height, pixels);
  munit_assert_int(pixels[(8 * 32 + 14) * 4 + 0], ==,  64);
  munit_assert_int(pixels[(8 * 32 + 14) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(8 * 32 + 14) * 4 + 2], ==,   0);
  return MUNIT_OK;
}

MunitTest test_integration[] = {
  {"/draw_triangle"          , test_draw_triangle          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/use_normal"             , test_use_normal             , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/draw_texturized_square" , test_draw_texturized_square , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/perspective_triangle"   , test_perspective_triangle   , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/draw_two_textures"      , test_draw_two_textures      , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/ambient_color"          , test_ambient_color          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/diffuse_color"          , test_diffuse_color          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/specular_color"         , test_specular_color         , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                      , NULL                        , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
