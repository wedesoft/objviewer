#include "fsim/group.h"
#include "test_group.h"
#include "test_helper.h"


static MunitResult test_empty_group(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 8);
  munit_assert_int(group->array->size, ==, 0);
  munit_assert_int(group->stride, ==, 8);
  munit_assert_ptr(group->material, ==, NULL);
  munit_assert_string_equal(group->name, "test");
  return MUNIT_OK;
}

static MunitResult test_copy_name(const MunitParameter params[], void *data)
{
  char test[2] = "x";
  group_t *group = make_group(test, 8);
  test[0] = 'y';
  munit_assert_string_equal(group->name, "x");
  return MUNIT_OK;
}

static MunitResult test_add_coordinate(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  add_vertex_data(group, 1, 2.5f);
  munit_assert_int(group->array->size, ==, 1);
  munit_assert_float(get_glfloat(group->array)[0], ==, 2.5f);
  return MUNIT_OK;
}

static MunitResult test_add_pair(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  add_vertex_data(group, 2, 2.5f, 3.5f);
  munit_assert_int(group->array->size, ==, 2);
  munit_assert_float(get_glfloat(group->array)[0], ==, 2.5f);
  munit_assert_float(get_glfloat(group->array)[1], ==, 3.5f);
  return MUNIT_OK;
}

static MunitResult test_add_three(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  add_vertex_data(group, 2, 0.36f, 0.48f);
  add_vertex_data(group, 1, 0.8f);
  munit_assert_int(group->array->size, ==, 3);
  munit_assert_float(get_glfloat(group->array)[0], ==, 0.36f);
  munit_assert_float(get_glfloat(group->array)[1], ==, 0.48f);
  munit_assert_float(get_glfloat(group->array)[2], ==, 0.80f);
  return MUNIT_OK;
}

static MunitResult test_empty_array(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  munit_assert_int(size_of_array(group), ==, 0);
  return MUNIT_OK;
}

static MunitResult test_size_of_array(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  add_vertex_data(group, 3, 2.5f, 3.5f, 5.5f);
  munit_assert_int(size_of_array(group), ==, sizeof(GLfloat) * 3);
  return MUNIT_OK;
}

static MunitResult test_no_indices(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  munit_assert_int(group->vertex_index->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_empty_indices(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  munit_assert_int(size_of_indices(group), ==, 0);
  return MUNIT_OK;
}

static MunitResult test_size_of_indices(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  int i;
  for (i=0; i<3; i++)
    add_vertex_data(group, 3, 0, 0, 0);
  add_triangle(group, 0, 1, 2);
  munit_assert_int(size_of_indices(group), ==, 3 * sizeof(int));
  return MUNIT_OK;
}

static MunitResult test_add_texcoord(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 5);
  add_vertex_data(group, 5, 2.5f, 3.5f, 5.5f, 0.25f, 0.75f);
  munit_assert_int(group->array->size, ==, 5);
  munit_assert_float(get_glfloat(group->array)[3], ==, 0.25f);
  munit_assert_float(get_glfloat(group->array)[4], ==, 0.75f);
  return MUNIT_OK;
}

static MunitResult test_add_triangle(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  int i;
  for (i=0; i<3; i++)
    add_vertex_data(group, 3, i % 2, 0, i / 2);
  add_triangle(group, 2, 0, 1);
  munit_assert_int(group->vertex_index->size, ==, 3);
  munit_assert_int(get_gluint(group->vertex_index)[0], ==, 2);
  munit_assert_int(get_gluint(group->vertex_index)[1], ==, 0);
  munit_assert_int(get_gluint(group->vertex_index)[2], ==, 1);
  return MUNIT_OK;
}

static MunitResult test_add_square(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  int i;
  for (i=0; i<4; i++)
    add_vertex_data(group, 3, i % 2, 0, i / 2);
  add_triangle(group, 2, 0, 1); extend_triangle(group, 3);
  munit_assert_int(group->vertex_index->size, ==, 6);
  munit_assert_int(get_gluint(group->vertex_index)[3], ==, 2);
  munit_assert_int(get_gluint(group->vertex_index)[4], ==, 1);
  munit_assert_int(get_gluint(group->vertex_index)[5], ==, 3);
  return MUNIT_OK;
}

static MunitResult test_add_pentagon(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 3);
  int i;
  for (i=0; i<4; i++)
    add_vertex_data(group, 3, i % 2, 0, i / 2);
  add_vertex_data(group, 3, 0.5, 0, 1.5);
  add_triangle(group, 0, 1, 3); extend_triangle(group, 4); extend_triangle(group, 2);
  munit_assert_int(group->vertex_index->size, ==, 9);
  munit_assert_int(get_gluint(group->vertex_index)[6], ==, 0);
  munit_assert_int(get_gluint(group->vertex_index)[7], ==, 4);
  munit_assert_int(get_gluint(group->vertex_index)[8], ==, 2);
  return MUNIT_OK;
}

static MunitResult test_use_material(const MunitParameter params[], void *data)
{
  group_t *group = make_group("test", 5);
  material_t *material = make_material();
  use_material(group, material);
  munit_assert_ptr(group->material, ==, material);
  return MUNIT_OK;
}

MunitTest test_group[] = {
  {"/empty_group"     , test_empty_group     , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/copy_name"       , test_copy_name       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_coordinate"  , test_add_coordinate  , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_pair"        , test_add_pair        , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_three"       , test_add_three       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/empty_array"     , test_empty_array     , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/size_of_array"   , test_size_of_array   , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_indices"      , test_no_indices      , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/empty_indices"   , test_empty_indices   , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/size_of_indices" , test_size_of_indices , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_texcoord"    , test_add_texcoord    , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_triangle"    , test_add_triangle    , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_square"      , test_add_square      , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_pentagon"    , test_add_pentagon    , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/use_material"    , test_use_material    , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL               , NULL                 , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL}
};
