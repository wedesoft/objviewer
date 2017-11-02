#include "test_integration.h"
#include "test_helper.h"
#include "fsim/object.h"
#include "fsim/program.h"
#include "fsim/projection.h"
#include "fsim/vertex_array_object.h"


static MunitResult test_draw_triangle(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface();
  add_vertex_data(surface, 3,  0.5f,  0.5f, 0.0f);
  add_vertex_data(surface, 3, -0.5f,  0.5f, 0.0f);
  add_vertex_data(surface, 3, -0.5f, -0.5f, 0.0f);
  add_triangle(surface, 0, 1, 2);
  program_t *program = make_program("vertex-identity.glsl", "fragment-blue.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 3);
  object_t *object = make_object("test");
  add_surface(object, surface);
  list_t *list = make_list();
  append_pointer(list, vertex_array_object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 1, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("draw_triangle.ppm", width, height, pixels);
  munit_assert_int(vertex_array_object->n_indices, ==, 3);
  munit_assert_int(pixels[0], ==,   0);
  munit_assert_int(pixels[1], ==, 255);
  munit_assert_int(pixels[2], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 0], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 2], ==, 255);
  return MUNIT_OK;
}

static MunitResult test_draw_two_surfaces(const MunitParameter params[], void *data)
{
  float coord[] = {0.5f, -0.5f};
  const char *fragment_shader_file_name[] = {"fragment-blue.glsl", "fragment-red.glsl"};
  object_t *object = make_object("test");
  list_t *list = make_list();
  int i;
  for (i=0;i<2; i++) {
    surface_t *surface = make_surface();
    float c = coord[i];
    add_vertex_data(surface, 3,     c,     c, 0.0f);
    add_vertex_data(surface, 3, -0.5f,  0.5f, 0.0f);
    add_vertex_data(surface, 3,  0.5f, -0.5f, 0.0f);
    add_triangle(surface, 0, 1, 2);
    program_t *program = make_program("vertex-identity.glsl", fragment_shader_file_name[i]);
    vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
    setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 3);
    add_surface(object, surface);
    append_pointer(list, vertex_array_object);
  };
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 1, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("draw_surfaces.ppm", width, height, pixels);
  munit_assert_int(pixels[0], ==,   0);
  munit_assert_int(pixels[1], ==, 255);
  munit_assert_int(pixels[2], ==,   0);
  munit_assert_int(pixels[( 8 * 32 + 14 ) * 4 + 0], ==, 255);
  munit_assert_int(pixels[( 8 * 32 + 14 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[( 8 * 32 + 14 ) * 4 + 2], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 18 ) * 4 + 0], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 18 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 18 ) * 4 + 2], ==, 255);
  return MUNIT_OK;
}

static MunitResult test_use_normal(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface();
  add_vertex_data(surface, 6,  0.5f,  0.5f, 0.0f,  0.0f,  0.0f, 1.0f);
  add_vertex_data(surface, 6, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 0.0f);
  add_vertex_data(surface, 6, -0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f);
  add_triangle(surface, 0, 1, 2);
  program_t *program = make_program("vertex-normal-identity.glsl", "fragment-normal.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point" , 3, 6);
  setup_vertex_attribute_pointer(vertex_array_object, "vector", 3, 6);
  object_t *object = make_object("test");
  list_t *list = make_list();
  add_surface(object, surface);
  append_pointer(list, vertex_array_object);
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
  surface_t *surface = make_surface();
  add_vertex_data(surface, 5, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f);
  add_vertex_data(surface, 5,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
  add_vertex_data(surface, 5, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f);
  add_vertex_data(surface, 5,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f);
  add_triangle(surface, 0, 1, 2); extend_triangle(surface, 3);
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-texture.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point"             , 3, 5);
  setup_vertex_attribute_pointer(vertex_array_object, "texture_coordinate", 2, 5);
  add_texture(vertex_array_object, make_texture("tex"), read_image("colors.png"));
  object_t *object = make_object("test");
  list_t *list = make_list();
  add_surface(object, surface);
  append_pointer(list, vertex_array_object);
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
  surface_t *surface = make_surface();
  add_vertex_data(surface, 3,  0.5f,  0.5f, -1.0f);
  add_vertex_data(surface, 3, -0.5f,  0.5f, -1.0f);
  add_vertex_data(surface, 3, -0.5f, -0.5f, -1.0f);
  add_triangle(surface, 0, 1, 2);
  program_t *program = make_program("vertex-projection.glsl", "fragment-blue.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 3);
  object_t *object = make_object("test");
  add_surface(object, surface);
  list_t *list = make_list();
  append_pointer(list, vertex_array_object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  uniform_matrix(program, "projection", projection(width, height, 0.1, 2.0, 90.0));
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(list);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("project_triangle.ppm", width, height, pixels);
  munit_assert_int(vertex_array_object->n_indices, ==, 3);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 0], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 14 ) * 4 + 2], ==, 255);
  return MUNIT_OK;
}

MunitTest test_integration[] = {
  {"/draw_triangle"          , test_draw_triangle          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/draw_two_surfaces"      , test_draw_two_surfaces      , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/use_normal"             , test_use_normal             , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/draw_texturized_square" , test_draw_texturized_square , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/perspective_triangle"   , test_perspective_triangle   , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                      , NULL                        , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
