#include "fsim/hash.h"
#include "test_hash.h"
#include "test_helper.h"


static MunitResult test_empty(const MunitParameter params[], void *data)
{
  hash_t *hash = make_hash();
  munit_assert_int(hash_find(hash, 25, 37), ==, 37);
  return MUNIT_OK;
}

static MunitResult test_add_entry(const MunitParameter params[], void *data)
{
  hash_t *hash = make_hash();
  hash_find(hash, 25, 37);
  munit_assert_int(hash_find(hash, 25, 12), ==, 37);
  return MUNIT_OK;
}

static MunitResult test_add_two_entries(const MunitParameter params[], void *data)
{
  hash_t *hash = make_hash();
  hash_find(hash, 25, 37);
  hash_find(hash, 12,  2);
  munit_assert_int(hash_find(hash, 25, 14), ==, 37);
  munit_assert_int(hash_find(hash, 12, 15), ==,  2);
  return MUNIT_OK;
}

static MunitResult test_key_pair(const MunitParameter params[], void *data)
{
  hash_t *hash = make_hash();
  hash_find_pair(hash, 12, 15, 37);
  munit_assert_int(hash_find_pair(hash, 12, 15, 100), ==, 37);
  return MUNIT_OK;
}

MunitTest test_hash[] = {
  {"/empty"          , test_empty          , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_entry"      , test_add_entry      , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add_two_entries", test_add_two_entries, test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/key_pair"       , test_key_pair       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL              , NULL                , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
