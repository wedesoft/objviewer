#include "fsim/vertex_array_object.h"
#include "test_vertex_array_object.h"
#include "test_helper.h"


static MunitResult test_vertex_attribute(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  group_t *group = make_group("test", 3);
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, group);
  munit_assert_int(vertex_array_object->n_attributes, ==, 1);
  munit_assert_int(vertex_array_object->attribute_pointer, ==, 3 * sizeof(float));
  return MUNIT_OK;
}

static MunitResult test_vertex_and_uv(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  group_t *group = make_group("test", 5);
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, group);
  munit_assert_int(vertex_array_object->n_attributes, ==, 2);
  munit_assert_int(vertex_array_object->attribute_pointer, ==, 5 * sizeof(float));
  return MUNIT_OK;
}

static MunitResult test_vertex_uv_and_normal(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  group_t *group = make_group("test", 8);
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, group);
  munit_assert_int(vertex_array_object->n_attributes, ==, 3);
  munit_assert_int(vertex_array_object->attribute_pointer, ==, 8 * sizeof(float));
  return MUNIT_OK;
}

static MunitResult test_vertex_and_normal(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  group_t *group = make_group("test", 6);
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, group);
  munit_assert_int(vertex_array_object->n_attributes, ==, 2);
  munit_assert_int(vertex_array_object->attribute_pointer, ==, 6 * sizeof(float));
  return MUNIT_OK;
}

static MunitResult test_no_textures(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, make_group("test", 5));
  munit_assert_int(vertex_array_object->texture->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_diffuse_texture(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 5);
  material_t *material = make_material();
  set_diffuse_texture(material, read_image("colors.png"));
  use_material(group, material);
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-texture.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, group);
  munit_assert_int(vertex_array_object->texture->size, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_two_textures(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 5);
  material_t *material = make_material();
  set_diffuse_texture(material, read_image("colors.png"));
  set_specular_texture(material, read_image("gray.png"));
  use_material(group, material);
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-two-textures.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, group);
  munit_assert_int(vertex_array_object->texture->size, ==, 2);
  return MUNIT_OK;
}

static MunitResult test_make_empty_vao_list(const MunitParameter params[], void *data)
{
  munit_assert_int(make_vertex_array_object_list(NULL, make_object("test"))->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_vao_list_entry(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 5);
  object_t *object = make_object("test");
  add_group(object, group);
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-texture.glsl");
  munit_assert_int(make_vertex_array_object_list(program, object)->size, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_vao_list_program(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 5);
  object_t *object = make_object("test");
  add_group(object, group);
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-texture.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  munit_assert_ptr(((vertex_array_object_t *)get_pointer(list)[0])->program, ==, program);
  return MUNIT_OK;
}

static MunitResult test_material(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 5);
  object_t *object = make_object("test");
  material_t *material = make_material();
  use_material(group, material);
  add_group(object, group);
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-texture.glsl");
  list_t *list = make_vertex_array_object_list(program, object);
  munit_assert_ptr(((vertex_array_object_t *)get_pointer(list)[0])->material, ==, material);
  return MUNIT_OK;
}

MunitTest test_vao[] = {
  {"/vertex_attribute"     , test_vertex_attribute     , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/vertex_and_uv"        , test_vertex_and_uv        , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/vertex_and_normal"    , test_vertex_and_normal    , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/vertex_uv_and_normal" , test_vertex_uv_and_normal , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_textures"          , test_no_textures          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/diffuse_texture"      , test_diffuse_texture      , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/two_textures"         , test_two_textures         , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/make_empty_vao_list"  , test_make_empty_vao_list  , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/vao_list_entry"       , test_vao_list_entry       , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/vao_list_program"     , test_vao_list_program     , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/material"             , test_material             , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                    , NULL                      , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
