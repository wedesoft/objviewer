#include "munit.h"

static MunitResult test_it(const MunitParameter params[], void *data)
{
  munit_assert(1);
  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  "/test",
  test_it,
  NULL,
  NULL,
  MUNIT_TEST_OPTION_NONE,
  NULL
};

static MunitSuite test_suite[] = {
  "",
  test_suite_tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  return munit_suite_main(&test_suite[0], (void*)NULL, argc, argv);
}
