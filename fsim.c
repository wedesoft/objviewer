#include <stdio.h>
#include <gc.h>
#include <GL/glut.h>
#include "CuTest.h"

typedef struct {
  GLfloat red;
  GLfloat green;
  GLfloat blue;
} rgb_t;

rgb_t make_rgb(GLfloat red, GLfloat green, GLfloat blue)
{
  rgb_t retval;
  retval.red   = red;
  retval.green = green;
  retval.blue  = blue;
  return retval;
}

void test_rgb(CuTest *tc)
{
  rgb_t c = make_rgb(0.5f, 0.75f, 0.25f);
  CuAssertDblEquals(tc, 0.50, c.red  , 1e-6);
  CuAssertDblEquals(tc, 0.75, c.green, 1e-6);
  CuAssertDblEquals(tc, 0.25, c.blue , 1e-6);
}

typedef struct {
  GLfloat x;
  GLfloat y;
  GLfloat z;
} vertex_t;

vertex_t make_vertex(GLfloat x, GLfloat y, GLfloat z)
{
  vertex_t retval;
  retval.x = x;
  retval.y = y;
  retval.z = z;
  return retval;
}

void test_vertex(CuTest *tc)
{
  vertex_t v = make_vertex(2.0f, 3.0f, 5.0f);
  CuAssertDblEquals(tc, 2.0f, v.x, 1e-6f);
  CuAssertDblEquals(tc, 3.0f, v.y, 1e-6f);
  CuAssertDblEquals(tc, 5.0f, v.z, 1e-6f);
}

typedef struct {
  int n_vertices;
  vertex_t *vertex;
  int n_indices;
  int *vertex_index;
} surface_t;

surface_t *make_surface(int max_vertices, int max_indices)
{
  surface_t *retval = GC_MALLOC(sizeof(surface_t));
  retval->n_vertices = 0;
  retval->vertex = GC_MALLOC(max_vertices * sizeof(vertex_t));
  retval->n_indices = 0;
  retval->vertex_index = GC_MALLOC(max_indices * sizeof(int));
  return retval;
}

surface_t *add_vertex(surface_t *surface, vertex_t vertex)
{
  surface->vertex[surface->n_vertices++] = vertex;
  return surface;
}

int size_of_vertices(surface_t *surface)
{
  return surface->n_vertices * sizeof(vertex_t);
}

void test_add_vertex(CuTest *tc)
{
  surface_t *surface = make_surface(3, 3);
  CuAssertIntEquals(tc, 0, surface->n_vertices);
  add_vertex(surface, make_vertex(2.5f, 3.5f, 5.5f));
  CuAssertIntEquals(tc, 1, surface->n_vertices);
  CuAssertDblEquals(tc, 2.5, surface->vertex[0].x, 1e-6);
  surface_t *retval = add_vertex(surface, make_vertex(1.5f, 4.5f, 7.5f));
  CuAssertDblEquals(tc, 1.5, surface->vertex[1].x, 1e-6);
  CuAssertPtrEquals(tc, surface, retval);
  CuAssertIntEquals(tc, 2 * sizeof(vertex_t), size_of_vertices(surface));
}

void build_facet(surface_t *surface, int number, int vertex_index)
{
  int n = surface->n_indices;
  if (number < 3) {
    surface->vertex_index[n] = vertex_index;
    surface->n_indices = n + 1;
  } else {
    build_facet(surface, 0, surface->vertex_index[n - 3]);
    build_facet(surface, 1, surface->vertex_index[n - 1]);
    build_facet(surface, 2, vertex_index);
  };
}

int size_of_indices(surface_t *surface)
{
  return surface->n_indices * sizeof(int);
}

void test_add_triangle(CuTest *tc)
{
  surface_t *surface = make_surface(3, 3);
  int i;
  for (i=0; i<3; i++)
    add_vertex(surface, make_vertex(i % 2, 0, i / 2));
  CuAssertIntEquals(tc, 0, surface->n_indices);
  build_facet(surface, 0, 2);
  build_facet(surface, 1, 0);
  build_facet(surface, 2, 1);
  CuAssertIntEquals(tc, 3, surface->n_indices);
  CuAssertIntEquals(tc, 2, surface->vertex_index[0]);
  CuAssertIntEquals(tc, 0, surface->vertex_index[1]);
  CuAssertIntEquals(tc, 1, surface->vertex_index[2]);
  CuAssertIntEquals(tc, 3 * sizeof(int), size_of_indices(surface));
}

void test_add_square(CuTest *tc)
{
  surface_t *surface = make_surface(4, 6);
  int i;
  for (i=0; i<4; i++)
    add_vertex(surface, make_vertex(i % 2, 0, i / 2));
  build_facet(surface, 0, 2);
  build_facet(surface, 1, 0);
  build_facet(surface, 2, 1);
  build_facet(surface, 3, 3);
  CuAssertIntEquals(tc, 6, surface->n_indices);
  CuAssertIntEquals(tc, 2, surface->vertex_index[3]);
  CuAssertIntEquals(tc, 1, surface->vertex_index[4]);
  CuAssertIntEquals(tc, 3, surface->vertex_index[5]);
}

void test_add_pentagon(CuTest *tc)
{
  surface_t *surface = make_surface(5, 9);
  int i;
  for (i=0; i<4; i++)
    add_vertex(surface, make_vertex(i % 2, 0, i / 2));
  add_vertex(surface, make_vertex(0.5, 0, 1.5));
  build_facet(surface, 0, 0);
  build_facet(surface, 1, 1);
  build_facet(surface, 2, 3);
  build_facet(surface, 3, 4);
  build_facet(surface, 4, 2);
  CuAssertIntEquals(tc, 9, surface->n_indices);
  CuAssertIntEquals(tc, 0, surface->vertex_index[6]);
  CuAssertIntEquals(tc, 4, surface->vertex_index[7]);
  CuAssertIntEquals(tc, 2, surface->vertex_index[8]);
}

typedef struct {
  rgb_t background_color;
  int n_surfaces;
  surface_t **surface;
} object_t;

object_t *make_object(rgb_t background_color, int max_surfaces)
{
  object_t *retval = GC_MALLOC(sizeof(object_t));
  retval->background_color = background_color;
  retval->n_surfaces = 0;
  retval->surface = GC_MALLOC(max_surfaces * sizeof(surface_t *));
  return retval;
}

object_t *add_surface(object_t *object, surface_t *surface)
{
  object->surface[object->n_surfaces++] = surface;
  return object;
}

void render(object_t *object)
{
  rgb_t c = object->background_color;
  glClearColor(c.red, c.green, c.blue, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void test_clear_buffer(CuTest *tc)
{
  object_t *object = make_object(make_rgb(0.75f, 0.25f, 0.125f), 1);
  render(object);
  glFlush();
  GLubyte pixel[4];
  glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
  CuAssertIntEquals(tc, 191, pixel[0]);
  CuAssertIntEquals(tc,  64, pixel[1]);
  CuAssertIntEquals(tc,  32, pixel[2]);
}

void test_add_surface(CuTest *tc)
{
  rgb_t black = make_rgb(0.0f, 0.0f, 0.0f);
  object_t *object = make_object(black, 1);
  CuAssertIntEquals(tc, 0, object->n_surfaces);
  object_t *retval = add_surface(object, add_vertex(make_surface(4, 1), make_vertex(2, 3, 5)));
  CuAssertIntEquals(tc, 1, object->n_surfaces);
  CuAssertDblEquals(tc, 5, object->surface[0]->vertex[0].z, 1e-6);
  CuAssertPtrEquals(tc, object, retval);
}

typedef struct {
  GLuint vertex_array_object;
  GLuint vertex_buffer_object;
  GLuint element_buffer_object;
} vertex_array_object_t;

vertex_array_object_t *make_vertex_array_object(surface_t *surface)
{
  vertex_array_object_t *retval = GC_MALLOC(sizeof(vertex_array_object_t));
  glGenVertexArrays(1, &retval->vertex_array_object);
  glBindVertexArray(retval->vertex_array_object);
  glGenBuffers(1, &retval->vertex_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, retval->vertex_buffer_object);
  glBufferData(GL_ARRAY_BUFFER, size_of_vertices(surface), surface->vertex, GL_STATIC_DRAW);
  glGenBuffers(1, &retval->element_buffer_object);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval->element_buffer_object);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices(surface), surface->vertex_index, GL_STATIC_DRAW);
  glBindVertexArray(0);
  return retval;
}

void free_vertex_array_object(vertex_array_object_t *target)
{
  glBindVertexArray(target->vertex_array_object);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &target->element_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &target->vertex_buffer_object);
  glDeleteBuffers(1, &target->vertex_array_object);
  glBindVertexArray(0);
}

void test_draw_triangle(CuTest *tc)
{
  surface_t *surface = make_surface(3, 3);
  CuAssertIntEquals(tc, 0, surface->n_vertices);
  add_vertex(surface, make_vertex( 0.5f,  0.5f, 0.0f));
  add_vertex(surface, make_vertex(-0.5f,  0.5f, 0.0f));
  add_vertex(surface, make_vertex(-0.5f, -0.5f, 0.0f));
  build_facet(surface, 0, 0);
  build_facet(surface, 1, 1);
  build_facet(surface, 2, 2);
  vertex_array_object_t *vao = make_vertex_array_object(surface);
  /* TODO: setup shader and attribute pointer, draw triangle, test output */
  free_vertex_array_object(vao);
}

CuSuite *opengl_suite(void)
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_rgb);
  SUITE_ADD_TEST(suite, test_vertex);
  SUITE_ADD_TEST(suite, test_add_vertex);
  SUITE_ADD_TEST(suite, test_clear_buffer);
  SUITE_ADD_TEST(suite, test_add_surface);
  SUITE_ADD_TEST(suite, test_add_triangle);
  SUITE_ADD_TEST(suite, test_add_square);
  SUITE_ADD_TEST(suite, test_add_pentagon);
  SUITE_ADD_TEST(suite, test_draw_triangle);
  return suite;
}

int main(int argc, char *argv[])
{
  GC_INIT();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA);
  glutInitWindowSize(32, 20);
  glutCreateWindow("test window");
	CuString *output = CuStringNew();
  CuSuite *suite = opengl_suite();
  CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
  return suite->failCount > 0 ? 1 : 0;
}
