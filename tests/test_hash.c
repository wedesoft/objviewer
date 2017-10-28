#include "fsim/hash.h"
#include "test_hash.h"
#include "test_helper.h"


static MunitResult test_empty(const MunitParameter params[], void *data)
{
  hash_create();
  munit_assert_int(hash_find(25), ==, -1);
  hash_destroy();
  return MUNIT_OK;
}

static MunitResult test_add_entry(const MunitParameter params[], void *data)
{
  hash_create();
  hash_enter(25, 37);
  munit_assert_int(hash_find(25), ==, 37);
  hash_destroy();
  return MUNIT_OK;
}

static MunitResult test_add_two_entries(const MunitParameter params[], void *data)
{
  hash_create();
  hash_enter(25, 37);
  hash_enter(12, 2);
  munit_assert_int(hash_find(25), ==, 37);
  munit_assert_int(hash_find(12), ==,  2);
  hash_destroy();
  return MUNIT_OK;
}

MunitTest test_hash[] = {
  {"/empty"          , test_empty          , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_entry"      , test_add_entry      , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_two_entries", test_add_two_entries, test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL              , NULL          , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
