#include "munit.h"
#include "test_rgb.h"
#include "test_vertex.h"
#include "test_normal.h"


static MunitSuite test_fsim[] = {
  {"/rgb"   , test_rgb   , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/vertex", test_vertex, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/normal", test_normal, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {NULL     , NULL       , NULL, 0, MUNIT_SUITE_OPTION_NONE}
};

static const MunitSuite test_suite[] = {
  "", NULL, test_fsim, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  return munit_suite_main(&test_suite[0], (void*)NULL, argc, argv);
}
