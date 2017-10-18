#include <gc.h>
#include "munit.h"
#include "test_helper.h"
#include "test_rgb.h"
#include "test_vertex.h"
#include "test_normal.h"
#include "test_surface.h"
#include "test_object.h"
#include "test_shader.h"
#include "test_program.h"
#include "test_vertex_array_object.h"
#include "test_image.h"
#include "test_texture.h"


static MunitSuite test_fsim[] = {
  {"/rgb"    , test_rgb    , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/vertex" , test_vertex , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/normal" , test_normal , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/surface", test_surface, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/object" , test_object , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/shader" , test_shader , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/program", test_program, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/vao"    , test_vao    , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/image"  , test_image  , NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {"/texture", test_texture, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {NULL      , NULL        , NULL, 0, MUNIT_SUITE_OPTION_NONE}
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
