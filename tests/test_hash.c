#include "fsim/hash.h"
#include "test_hash.h"
#include "test_helper.h"


static MunitResult test_no_index(const MunitParameter params[], void *data)
{
  hash_t *hash = make_hash();
  munit_assert_int(hash_find_index(hash, 2, 3, 5, 37), ==, 37);
  return MUNIT_OK;
}

static MunitResult test_add_index(const MunitParameter params[], void *data)
{
  hash_t *hash = make_hash();
  hash_find_index(hash, 2, 3, 5, 37);
  munit_assert_int(hash_find_index(hash, 2, 3, 5, 12), ==, 37);
  return MUNIT_OK;
}

static MunitResult test_add_two_indices(const MunitParameter params[], void *data)
{
  hash_t *hash = make_hash();
  hash_find_index(hash, 2, 3, 5, 37);
  hash_find_index(hash, 1, 2, 4,  2);
  munit_assert_int(hash_find_index(hash, 2, 3, 5, 14), ==, 37);
  munit_assert_int(hash_find_index(hash, 1, 2, 4, 15), ==,  2);
  return MUNIT_OK;
}

static MunitResult test_no_pointer(const MunitParameter params[], void *data)
{
  hash_t *hash = make_hash();
  material_t *material = make_material();
  munit_assert_ptr(hash_find_material(hash, "material", material), ==, material);
  return MUNIT_OK;
}

static MunitResult test_add_material(const MunitParameter params[], void *data)
{
  hash_t *hash = make_hash();
  material_t *metal = make_material();
  hash_find_material(hash, "metal", metal);
  munit_assert_ptr(hash_find_material(hash, "metal", NULL), ==, metal);
  return MUNIT_OK;
}

static MunitResult test_add_two_materials(const MunitParameter params[], void *data)
{
  hash_t *hash = make_hash();
  material_t *stone = make_material();
  material_t *metal = make_material();
  hash_find_material(hash, "stone", stone);
  hash_find_material(hash, "metal", metal);
  munit_assert_ptr(hash_find_material(hash, "stone", NULL), ==, stone);
  munit_assert_ptr(hash_find_material(hash, "metal", NULL), ==, metal);
  return MUNIT_OK;
}

MunitTest test_hash[] = {
  {"/no_index"         , test_no_index         , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_index"        , test_add_index        , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_two_indices"  , test_add_two_indices  , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_pointer"       , test_no_pointer       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_material"     , test_add_material     , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_two_materials", test_add_two_materials, test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                , NULL                  , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
