#include "fsim/parser.h"
#include "fsim/list.h"
#include "test_helper.h"


extern object_t *parse_string_core(program_t *program, const char *text);
extern list_t *parse_vertex;
extern list_t *parse_uv;
extern list_t *parse_normal;
extern list_t *parse_surface;


static MunitResult test_empty(const MunitParameter params[], void *data)
{
  munit_assert_ptr(parse_string(NULL, ""), ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_object(const MunitParameter params[], void *data)
{
  munit_assert_ptr(parse_string(NULL, "o test"), !=, NULL);
  return MUNIT_OK;
}

static MunitResult test_object_name(const MunitParameter params[], void *data)
{
  munit_assert_string_equal(parse_string(NULL, "o test")->name, "test");
  return MUNIT_OK;
}

static MunitResult test_error(const MunitParameter params[], void *data)
{
  munit_assert_ptr(parse_string(NULL, "o test\n?"), ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_no_newline_in_name(const MunitParameter params[], void *data)
{
  munit_assert_string_equal(parse_string(NULL, "o test\n")->name, "test");
  return MUNIT_OK;
}

static MunitResult test_no_vertices(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "");
  munit_assert_int(parse_vertex->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_read_vertex(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nv 10 2.5 -3.25");
  munit_assert_int(parse_vertex->size, ==, 3);
  munit_assert_float(get_glfloat(parse_vertex)[0], ==, 10.0f);
  munit_assert_float(get_glfloat(parse_vertex)[1], ==,  2.5f);
  munit_assert_float(get_glfloat(parse_vertex)[2], ==, -3.25f);
  return MUNIT_OK;
}

static MunitResult test_two_vertices(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nv 10 2.5 -3.25\nv .5 +1 -.25");
  munit_assert_int(parse_vertex->size, ==, 6);
  munit_assert_float(get_glfloat(parse_vertex)[3], ==,  0.5f);
  munit_assert_float(get_glfloat(parse_vertex)[4], ==,  1.0f);
  munit_assert_float(get_glfloat(parse_vertex)[5], ==, -0.25f);
  return MUNIT_OK;
}

static MunitResult test_cleanup_vertices(const MunitParameter params[], void *data)
{
  parse_string(NULL, "o test\nv 10 2.5 3.25");
  munit_assert_ptr(parse_vertex, ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_no_surfaces(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "");
  munit_assert_int(parse_surface->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_start_surface(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\ns off");
  munit_assert_int(parse_surface->size, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_two_surfaces(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\ns off\ns off");
  munit_assert_int(parse_surface->size, ==, 2);
  return MUNIT_OK;
}

static MunitResult test_cleanup_surfaces(const MunitParameter params[], void *data)
{
  parse_string(NULL, "o test");
  munit_assert_ptr(parse_surface, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_facet(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\ns off\nf 1 2 3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->vertex_index->size, ==, 3);
  return MUNIT_OK;
}

static MunitResult test_indices(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\ns off\nf 1 2 3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(get_gluint(surface->vertex_index)[0], ==, 0);
  munit_assert_int(get_gluint(surface->vertex_index)[1], ==, 1);
  munit_assert_int(get_gluint(surface->vertex_index)[2], ==, 2);
  return MUNIT_OK;
}

static MunitResult test_coord_count(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\ns off\nf 1 2 3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->array->size, ==, 9);
  return MUNIT_OK;
}

static MunitResult test_copy_coords(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\ns off\nf 1 2 3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_float(get_glfloat(surface->array)[0], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[1], ==, 3.0f);
  munit_assert_float(get_glfloat(surface->array)[2], ==, 5.0f);
  munit_assert_float(get_glfloat(surface->array)[3], ==, 3.0f);
  munit_assert_float(get_glfloat(surface->array)[4], ==, 5.0f);
  munit_assert_float(get_glfloat(surface->array)[5], ==, 7.0f);
  munit_assert_float(get_glfloat(surface->array)[6], ==, 7.0f);
  munit_assert_float(get_glfloat(surface->array)[7], ==, 5.0f);
  munit_assert_float(get_glfloat(surface->array)[8], ==, 3.0f);
  return MUNIT_OK;
}

static MunitResult test_shuffle_coords(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\ns off\nf 1 3 2");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_float(get_glfloat(surface->array)[0], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[1], ==, 3.0f);
  munit_assert_float(get_glfloat(surface->array)[2], ==, 5.0f);
  munit_assert_float(get_glfloat(surface->array)[3], ==, 7.0f);
  munit_assert_float(get_glfloat(surface->array)[4], ==, 5.0f);
  munit_assert_float(get_glfloat(surface->array)[5], ==, 3.0f);
  munit_assert_float(get_glfloat(surface->array)[6], ==, 3.0f);
  munit_assert_float(get_glfloat(surface->array)[7], ==, 5.0f);
  munit_assert_float(get_glfloat(surface->array)[8], ==, 7.0f);
  return MUNIT_OK;
}

static MunitResult test_generate_indices(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\ns off\nf 1 3 2");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(get_gluint(surface->vertex_index)[0], ==, 0);
  munit_assert_int(get_gluint(surface->vertex_index)[1], ==, 1);
  munit_assert_int(get_gluint(surface->vertex_index)[2], ==, 2);
  return MUNIT_OK;
}

static MunitResult test_two_facets(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\nv 9 7 5\ns off\nf 1 2 3\nf 1 4 3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->vertex_index->size, ==, 6);
  return MUNIT_OK;
}

static MunitResult test_reuse_vertices(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\nv 9 7 5\ns off\nf 1 2 3\nf 4 3 1");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(get_gluint(surface->vertex_index)[0], ==, 0);
  munit_assert_int(get_gluint(surface->vertex_index)[1], ==, 1);
  munit_assert_int(get_gluint(surface->vertex_index)[2], ==, 2);
  munit_assert_int(get_gluint(surface->vertex_index)[3], ==, 3);
  munit_assert_int(get_gluint(surface->vertex_index)[4], ==, 2);
  munit_assert_int(get_gluint(surface->vertex_index)[5], ==, 0);
  return MUNIT_OK;
}

static MunitResult test_square_facet(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\nv 9 7 5\ns off\nf 1 2 3 4");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(get_gluint(surface->vertex_index)[0], ==, 0);
  munit_assert_int(get_gluint(surface->vertex_index)[1], ==, 1);
  munit_assert_int(get_gluint(surface->vertex_index)[2], ==, 2);
  munit_assert_int(get_gluint(surface->vertex_index)[3], ==, 0);
  munit_assert_int(get_gluint(surface->vertex_index)[4], ==, 2);
  munit_assert_int(get_gluint(surface->vertex_index)[5], ==, 3);
  return MUNIT_OK;
}

static MunitResult test_no_vao(const MunitParameter params[], void *data)
{
  object_t *object = parse_string(NULL, "o test");
  munit_assert_int(object->vertex_array_object->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_convert_to_vao(const MunitParameter params[], void *data)
{
  object_t *object = parse_string(NULL, "o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\ns off\nf 1 2 3");
  munit_assert_int(object->vertex_array_object->size, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_set_program(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-identity.glsl", "fragment-blue.glsl");
  object_t *object = parse_string(program, "o test\nv 2 3 5\nv 3 5 7\nv 7 5 3\ns off\nf 1 2 3");
  vertex_array_object_t *vertex_array_object = get_pointer(object->vertex_array_object)[0];
  munit_assert_ptr(vertex_array_object->program, ==, program);
  return MUNIT_OK;
}

static MunitResult test_draw_object(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-identity.glsl", "fragment-blue.glsl");
  object_t *object =
    parse_string(program, "o square\nv 0.5 0.5 0.0\nv -0.5 0.5 0.0\nv -0.5 -0.5 0.0\nv 0.5 -0.5 0.0\ns off\nf 1 2 3 4\n");
  vertex_array_object_t *vertex_array_object = get_pointer(object->vertex_array_object)[0];
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 3);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(object);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("draw_object.ppm", width, height, pixels);
  munit_assert_int(pixels[(10 * 32 + 16) * 4 + 0], ==,   0);
  munit_assert_int(pixels[(10 * 32 + 16) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(10 * 32 + 16) * 4 + 2], ==, 255);
  return MUNIT_OK;
}

static MunitResult test_no_texcoord(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "");
  munit_assert_int(parse_uv->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_cleanup_texcoords(const MunitParameter params[], void *data)
{
  parse_string(NULL, "o test");
  munit_assert_ptr(parse_uv, ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_read_texcoord(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nvt 0.5 0.25");
  munit_assert_int(parse_uv->size, ==, 2);
  munit_assert_float(get_glfloat(parse_uv)[0], ==, 0.50f);
  munit_assert_float(get_glfloat(parse_uv)[1], ==, 0.25f);
  return MUNIT_OK;
}

static MunitResult test_two_texcoords(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nvt 0.5 0.25\nvt 0.75 1.0");
  munit_assert_int(parse_uv->size, ==, 4);
  munit_assert_float(get_glfloat(parse_uv)[2], ==, 0.75f);
  munit_assert_float(get_glfloat(parse_uv)[3], ==, 1.00f);
  return MUNIT_OK;
}

static MunitResult test_uv_facet(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvt 0 0\nvt 0 1\nvt 1 0\ns off\nf 1/1 2/2 3/3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->vertex_index->size, ==, 3);
  return MUNIT_OK;
}

static MunitResult test_uv_indices(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvt 0 0\nvt 0 1\nvt 1 0\ns off\nf 1/1 2/2 3/3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(get_gluint(surface->vertex_index)[0], ==, 0);
  munit_assert_int(get_gluint(surface->vertex_index)[1], ==, 1);
  munit_assert_int(get_gluint(surface->vertex_index)[2], ==, 2);
  return MUNIT_OK;
}

static MunitResult test_uv_added(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvt 0 0\nvt 0 1\nvt 1 0\ns off\nf 1/1 2/2 3/3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->array->size, ==, 15);
  return MUNIT_OK;
}

static MunitResult test_copy_uv(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvt 0 0\nvt 0 1\nvt 1 0\ns off\nf 1/1 2/2 3/3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_float(get_glfloat(surface->array)[0], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[1], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[2], ==,-1.0f);
  munit_assert_float(get_glfloat(surface->array)[3], ==, 0.0f);
  munit_assert_float(get_glfloat(surface->array)[4], ==, 0.0f);
  munit_assert_float(get_glfloat(surface->array)[5], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[6], ==, 3.0f);
  munit_assert_float(get_glfloat(surface->array)[7], ==,-1.0f);
  munit_assert_float(get_glfloat(surface->array)[8], ==, 0.0f);
  munit_assert_float(get_glfloat(surface->array)[9], ==, 1.0f);
  return MUNIT_OK;
}

static MunitResult test_different_uv_index(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvt 0 0\nvt 0 1\nvt 1 0\ns off\nf 1/2 2/3 3/1");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_float(get_glfloat(surface->array)[0], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[1], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[2], ==,-1.0f);
  munit_assert_float(get_glfloat(surface->array)[3], ==, 0.0f);
  munit_assert_float(get_glfloat(surface->array)[4], ==, 1.0f);
  return MUNIT_OK;
}

static MunitResult test_reuse_uv(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvt 0 0\nvt 0 1\nvt 1 0\ns off\nf 1/1 1/1 2/2");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->array->size, ==, 10);
  return MUNIT_OK;
}

static MunitResult test_uv_in_hash_key(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvt 0 0\nvt 0 1\nvt 1 0\ns off\nf 1/1 1/2 1/3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->array->size, ==, 15);
  return MUNIT_OK;
}

static MunitResult test_vertex_and_uv_key(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvt 0 0\nvt 0 1\nvt 1 0\ns off\nf 1/1 2/1 3/1");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->array->size, ==, 15);
  return MUNIT_OK;
}

static MunitResult test_draw_with_uv(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-uv.glsl", "fragment-uv.glsl");
  object_t *object =
    parse_string(program,"o test\nv -0.5 -0.5 -1\nv -0.5 0.5 -1\nv 0.5 -0.5 -1\nvt 0 0\nvt 0 1\nvt 1 0\ns off\nf 1/1 2/2 3/3");
  vertex_array_object_t *vertex_array_object = get_pointer(object->vertex_array_object)[0];
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 5);
  setup_vertex_attribute_pointer(vertex_array_object, "texcoord", 2, 5);
  add_texture(vertex_array_object, make_texture("tex"), read_image("colors.png"));
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(object);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("draw_with_uv.ppm", width, height, pixels);
  munit_assert_int(pixels[( 8 * 32 + 10 ) * 4 + 0], ==, 255);
  munit_assert_int(pixels[( 8 * 32 + 10 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[( 8 * 32 + 10 ) * 4 + 2], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 10 ) * 4 + 0], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 10 ) * 4 + 1], ==,   0);
  munit_assert_int(pixels[(12 * 32 + 10 ) * 4 + 2], ==, 255);
  return MUNIT_OK;
}

static MunitResult test_no_normal(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "");
  munit_assert_int(parse_normal->size, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_cleanup_normals(const MunitParameter params[], void *data)
{
  parse_string(NULL, "");
  munit_assert_ptr(parse_normal, ==, NULL);
  return MUNIT_OK;
}

static MunitResult test_read_normal(const MunitParameter params[], void *data)
{
  parse_string_core(NULL, "o test\nvn 0.36 0.48 0.8");
  munit_assert_int(parse_normal->size, ==, 3);
  munit_assert_float(get_glfloat(parse_normal)[0], ==, 0.36f);
  munit_assert_float(get_glfloat(parse_normal)[1], ==, 0.48f);
  munit_assert_float(get_glfloat(parse_normal)[2], ==, 0.80f);
  return MUNIT_OK;
}

static MunitResult test_normal_facet(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvn 1 0 0\nvn 0 1 0\nvn 0 0 1\ns off\nf 1//1 2//2 3//3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->vertex_index->size, ==, 3);
  return MUNIT_OK;
}

static MunitResult test_normal_indices(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvn 1 0 0\nvn 0 1 0\nvn 0 0 1\ns off\nf 1//1 2//2 3//3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(get_gluint(surface->vertex_index)[0], ==, 0);
  munit_assert_int(get_gluint(surface->vertex_index)[1], ==, 1);
  munit_assert_int(get_gluint(surface->vertex_index)[2], ==, 2);
  return MUNIT_OK;
}

static MunitResult test_normals_added(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvn 1 0 0\nvn 0 1 0\nvn 0 0 1\ns off\nf 1//1 2//2 3//3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->array->size, ==, 18);
  return MUNIT_OK;
}

static MunitResult test_copy_normal(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvn 1 0 0\nvn 0 1 0\nvn 0 0 1\ns off\nf 1//1 2//2 3//3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_float(get_glfloat(surface->array)[ 0], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[ 1], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[ 2], ==,-1.0f);
  munit_assert_float(get_glfloat(surface->array)[ 3], ==, 1.0f);
  munit_assert_float(get_glfloat(surface->array)[ 4], ==, 0.0f);
  munit_assert_float(get_glfloat(surface->array)[ 5], ==, 0.0f);
  munit_assert_float(get_glfloat(surface->array)[ 6], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[ 7], ==, 3.0f);
  munit_assert_float(get_glfloat(surface->array)[ 8], ==,-1.0f);
  munit_assert_float(get_glfloat(surface->array)[ 9], ==, 0.0f);
  munit_assert_float(get_glfloat(surface->array)[10], ==, 1.0f);
  munit_assert_float(get_glfloat(surface->array)[11], ==, 0.0f);
  return MUNIT_OK;
}

static MunitResult test_different_normal_index(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvn 1 0 0\nvn 0 1 0\nvn 0 0 1\ns off\nf 1//2 2//3 3//1");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_float(get_glfloat(surface->array)[0], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[1], ==, 2.0f);
  munit_assert_float(get_glfloat(surface->array)[2], ==,-1.0f);
  munit_assert_float(get_glfloat(surface->array)[3], ==, 0.0f);
  munit_assert_float(get_glfloat(surface->array)[4], ==, 1.0f);
  munit_assert_float(get_glfloat(surface->array)[5], ==, 0.0f);
  return MUNIT_OK;
}

static MunitResult test_reuse_normal(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvn 1 0 0\nvn 0 1 0\nvn 0 0 1\ns off\nf 1//1 1//1 2//2");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->array->size, ==, 12);
  return MUNIT_OK;
}

static MunitResult test_normal_in_hash_key(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvn 1 0 0\nvn 0 1 0\nvn 0 0 1\ns off\nf 1//1 1//2 1//3");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->array->size, ==, 18);
  return MUNIT_OK;
}

static MunitResult test_vertex_and_normal_key(const MunitParameter params[], void *data)
{
  parse_string_core(NULL,"o test\nv 2 2 -1\nv 2 3 -1\nv 3 2 -1\nvn 1 0 0\nvn 0 1 0\nvn 0 0 1\ns off\nf 1//1 2//1 3//1");
  surface_t *surface = get_pointer(parse_surface)[0];
  munit_assert_int(surface->array->size, ==, 18);
  return MUNIT_OK;
}

static MunitResult test_draw_with_normal(const MunitParameter params[], void *data)
{
  program_t *program = make_program("vertex-normal-identity.glsl", "fragment-normal.glsl");
  object_t *object =
    parse_string(program,"o test\nv 0.5 0.5 0\nv -0.5 0.5 0\nv -0.5 -0.5 0\nvn 0 0 1\nvn 0 1 0\nvn 1 0 0\ns off\nf 1//1 2//2 3//3");
  vertex_array_object_t *vertex_array_object = get_pointer(object->vertex_array_object)[0];
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 6);
  setup_vertex_attribute_pointer(vertex_array_object, "vector", 3, 6);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  render(object);
  glFinish();
  unsigned char *pixels = read_pixels();
  write_ppm("draw_normal.ppm", width, height, pixels);
  munit_assert_int(pixels[( 5 * 32 + 8 ) * 4 + 0], >=, 192);
  munit_assert_int(pixels[(14 * 32 + 8 ) * 4 + 0], < ,  64);
  munit_assert_int(pixels[(14 * 32 + 8 ) * 4 + 1], >=, 192);
  return MUNIT_OK;
}

MunitTest test_parser[] = {
  {"/empty"                 , test_empty                 , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/object"                , test_object                , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/object_name"           , test_object_name           , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/error"                 , test_error                 , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_newline_in_name"    , test_no_newline_in_name    , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_vertices"           , test_no_vertices           , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/read_vertex"           , test_read_vertex           , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/two_vertices"          , test_two_vertices          , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/cleanup_vertices"      , test_cleanup_vertices      , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_surfaces"           , test_no_surfaces           , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/start_surface"         , test_start_surface         , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/two_surfaces"          , test_two_surfaces          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/cleanup_surfaces"      , test_cleanup_surfaces      , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/facet"                 , test_facet                 , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/indices"               , test_indices               , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/coord_count"           , test_coord_count           , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/copy_coords"           , test_copy_coords           , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/shuffle_coords"        , test_shuffle_coords        , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/generate_indices"      , test_generate_indices      , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/two_facets"            , test_two_facets            , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/reuse_vertices"        , test_reuse_vertices        , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/square_facet"          , test_square_facet          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_vao"                , test_no_vao                , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/convert_to_vao"        , test_convert_to_vao        , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/set_program"           , test_set_program           , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/draw_object"           , test_draw_object           , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_texcoord"           , test_no_texcoord           , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/cleanup_texcoords"     , test_cleanup_texcoords     , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/read_texcoord"         , test_read_texcoord         , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/two_texcoords"         , test_two_texcoords         , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/uv_facet"              , test_uv_facet              , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/reuse_uv"              , test_reuse_uv              , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/uv_indices"            , test_uv_indices            , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/uv_added"              , test_uv_added              , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/copy_uv"               , test_copy_uv               , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/different_uv_index"    , test_different_uv_index    , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/uv_in_hash_key"        , test_uv_in_hash_key        , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/vertex_and_uv_key"     , test_vertex_and_uv_key     , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/draw_with_uv"          , test_draw_with_uv          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/no_normal  "           , test_no_normal             , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/cleanup_normals"       , test_cleanup_normals       , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/read_normal"           , test_read_normal           , test_setup_gc, test_teardown_gc, MUNIT_TEST_OPTION_NONE, NULL},
  {"/normal_facet"          , test_normal_facet          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/normal_indices"        , test_normal_indices        , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/normals_added"         , test_normals_added         , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/copy_normal"           , test_copy_normal           , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/different_normal_index", test_different_normal_index, test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/reuse_normal"          , test_reuse_normal          , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/normal_in_hash_key"    , test_normal_in_hash_key    , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/vertex_and_normal_key" , test_vertex_and_normal_key , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {"/draw_with_normal"      , test_draw_with_normal      , test_setup_gl, test_teardown_gl, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL                     , NULL                       , NULL         , NULL            , MUNIT_TEST_OPTION_NONE, NULL}
};
