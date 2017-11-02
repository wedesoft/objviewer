#include "fsim/vertex_array_object.h"
#include "test_vertex_array_object.h"
#include "test_helper.h"


static MunitResult test_no_attribute_pointers(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  munit_assert_int(program->n_attributes, ==, 0);
  munit_assert_int(program->attribute_pointer, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_add_attribute_pointer(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  surface_t *surface = make_surface();
  add_vertex_data(surface, 3, 0.5f,  0.5f, 0.0f);
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 5);
  munit_assert_int(program->n_attributes, ==, 1);
  munit_assert_int(program->attribute_pointer, ==, 3 * sizeof(float));
  return MUNIT_OK;
}

static MunitResult test_add_two_attribute_pointers(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  surface_t *surface = make_surface();
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point"             , 3, 5);
  setup_vertex_attribute_pointer(vertex_array_object, "texture_coordinate", 2, 5);
  munit_assert_int( program->n_attributes, ==, 2);
  munit_assert_int(program->attribute_pointer, ==, 5 * sizeof(float));
  return MUNIT_OK;
}

static MunitResult test_no_textures(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, make_surface());
  munit_assert_int(vertex_array_object->texture->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_add_texture(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface();
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-texture.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  texture_t *texture = make_texture("tex");
  add_texture(vertex_array_object, texture, read_image("colors.png"));
  munit_assert_int(vertex_array_object->texture->size, ==, 1);
  munit_assert_ptr(get_pointer(vertex_array_object->texture)[0], ==, texture);
  return MUNIT_OK;
}

static MunitResult test_make_empty_vao_list(const MunitParameter params[], void *data)
{
  munit_assert_int(make_vertex_array_object_list(NULL, make_object("test"))->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_vao_list_entry(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface();
  object_t *object = make_object("test");
  add_surface(object, surface);
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-texture.glsl");
  munit_assert_int(make_vertex_array_object_list(program, object)->size, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_vao_list_program(const MunitParameter params[], void *data)
{
  surface_t *surface = make_surface();
  object_t *object = make_object("test");
  add_surface(object, surface);
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-texture.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  munit_assert_ptr(((vertex_array_object_t *)get_pointer(list)[0])->program, ==, program);
  return MUNIT_OK;
}

MunitTest test_vao[] = {
  {"/no_attribute_pointers"     , test_no_attribute_pointers     , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_attribute_pointer"     , test_add_attribute_pointer     , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_two_attribute_pointers", test_add_two_attribute_pointers, test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_textures"               , test_no_textures               , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_texture"               , test_add_texture               , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/make_empty_vao_list"       , test_make_empty_vao_list       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/vao_list_entry"            , test_vao_list_entry            , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/vao_list_program"          , test_vao_list_program          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                         , NULL                           , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
