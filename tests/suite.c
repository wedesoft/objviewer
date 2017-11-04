#include <gc.h>
#include "munit.h"
#include "test_helper.h"
#include "test_surface.h"
#include "test_object.h"
#include "test_shader.h"
#include "test_program.h"
#include "test_vertex_array_object.h"
#include "test_image.h"
#include "test_texture.h"
#include "test_projection.h"
#include "test_list.h"
#include "test_hash.h"
#include "test_parser.h"
#include "test_material.h"
#include "test_integration.h"


static MunitSuite test_fsim[] = {
  {"/surface"    , test_surface    , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/object"     , test_object     , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/shader"     , test_shader     , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/program"    , test_program    , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/vao"        , test_vao        , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/image"      , test_image      , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/texture"    , test_texture    , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/projection" , test_projection , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/list"       , test_list       , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/hash"       , test_hash       , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/parser"     , test_parser     , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/material"   , test_material   , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/integration", test_integration, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {NULL          , NULL            , NULL, 0, MUNIT_SUITE_OPTION_NONE}
};

static const MunitSuite test_suite[] = {
  "", NULL, test_fsim, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  GC_INIT();
  int result = munit_suite_main(&test_suite[0], (void*)NULL, argc, argv);
  GC_gcollect();
  return result;
}
