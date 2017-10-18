#include "test_vertex.h"
#include "vertex.h"


static MunitResult test_make_vertex(const MunitParameter params[], void *data)
{
  vertex_t vertex = make_vertex(2.0f, 3.0f, 5.0f);
  munit_assert_float(vertex.x, ==, 2.0f);
  munit_assert_float(vertex.y, ==, 3.0f);
  munit_assert_float(vertex.z, ==, 5.0f);
  return MUNIT_OK;
}

MunitTest test_vertex[] = {
  {"/make_vertex", test_make_vertex, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL          , NULL            , NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
