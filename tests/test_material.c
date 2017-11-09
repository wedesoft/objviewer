#include "fsim/hash.h"
#include "test_hash.h"
#include "test_helper.h"


static MunitResult test_default(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  munit_assert_float(material->ambient[0], ==, 0.0f);
  munit_assert_float(material->ambient[1], ==, 0.0f);
  munit_assert_float(material->ambient[2], ==, 0.0f);
  munit_assert_float(material->diffuse[0], ==, 0.0f);
  munit_assert_float(material->diffuse[1], ==, 0.0f);
  munit_assert_float(material->diffuse[2], ==, 0.0f);
  munit_assert_float(material->specular[0], ==, 0.0f);
  munit_assert_float(material->specular[1], ==, 0.0f);
  munit_assert_float(material->specular[2], ==, 0.0f);
  munit_assert_float(material->specular_exponent, ==, 1.0f);
  munit_assert_float(material->optical_density, ==, 1.0f);
  munit_assert_float(material->disolve, ==, 1.0f);
  munit_assert_ptr(material->texture, ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_set_texture(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  image_t *image = read_image("colors.png");
  set_texture(material, image);
  munit_assert_ptr(material->texture, !=, NULL);
  return MUNIT_OK;
}

static MunitResult test_texture_not_found(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  image_t *image = read_image("nosuchfile.png");
  set_texture(material, image);
  munit_assert_ptr(material->texture, ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_set_ambient(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  set_ambient(material, 0.25f, 0.5f, 1.0f);
  munit_assert_float(material->ambient[0], ==, 0.25f);
  munit_assert_float(material->ambient[1], ==, 0.50f);
  munit_assert_float(material->ambient[2], ==, 1.00f);
  return MUNIT_OK;
}

static MunitResult test_set_diffuse(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  set_diffuse(material, 0.25f, 0.5f, 1.0f);
  munit_assert_float(material->diffuse[0], ==, 0.25f);
  munit_assert_float(material->diffuse[1], ==, 0.50f);
  munit_assert_float(material->diffuse[2], ==, 1.00f);
  return MUNIT_OK;
}

static MunitResult test_set_specular(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  set_specular(material, 0.25f, 0.5f, 1.0f);
  munit_assert_float(material->specular[0], ==, 0.25f);
  munit_assert_float(material->specular[1], ==, 0.50f);
  munit_assert_float(material->specular[2], ==, 1.00f);
  return MUNIT_OK;
}

static MunitResult test_set_specular_exponent(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  set_specular_exponent(material, 6.5f);
  munit_assert_float(material->specular_exponent, ==, 6.5f);
  return MUNIT_OK;
}

static MunitResult test_set_optical_density(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  set_optical_density(material, 1.5f);
  munit_assert_float(material->optical_density, ==, 1.5f);
  return MUNIT_OK;
}

static MunitResult test_set_disolve(const MunitParameter params[], void *data)
{
  material_t *material = make_material();
  set_disolve(material, 0.5f);
  munit_assert_float(material->disolve, ==, 0.5f);
  return MUNIT_OK;
}

MunitTest test_material[] = {
  {"/default"              , test_default               , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/set_texture"          , test_set_texture           , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/texture_not_found"    , test_texture_not_found     , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/set_ambient"          , test_set_ambient           , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/set_diffuse"          , test_set_diffuse           , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/set_specular"         , test_set_specular          , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/set_specular_exponent", test_set_specular_exponent , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/set_optical_density"  , test_set_optical_density   , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/set_disolve"          , test_set_disolve           , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                    , NULL                       , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
