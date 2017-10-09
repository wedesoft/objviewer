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
} surface_t;

surface_t *make_surface(int max_vertices)
{
  surface_t *retval = GC_MALLOC(sizeof(surface_t));
  retval->n_vertices = 0;
  retval->vertex = GC_MALLOC(max_vertices * sizeof(vertex_t));
  return retval;
}

surface_t *add_vertex(surface_t *surface, vertex_t vertex)
{
  surface->vertex[surface->n_vertices++] = vertex;
  return surface;
}

void test_add_vertex(CuTest *tc)
{
  surface_t *surface = make_surface(4);
  CuAssertIntEquals(tc, 0, surface->n_vertices);
  add_vertex(surface, make_vertex(2.5f, 3.5f, 5.5f));
  CuAssertDblEquals(tc, 2.5, surface->vertex[0].x, 1e-6);
  surface_t *retval = add_vertex(surface, make_vertex(1.5f, 4.5f, 7.5f));
  CuAssertDblEquals(tc, 1.5, surface->vertex[1].x, 1e-6);
  CuAssertPtrEquals(tc, surface, retval);
}

typedef struct {
  rgb_t background_color;
  int n_surfaces;
  surface_t **surface;
} scene_t;

scene_t *make_scene(rgb_t background_color, int max_surfaces)
{
  scene_t *retval = GC_MALLOC(sizeof(scene_t));
  retval->background_color = background_color;
  retval->n_surfaces = 0;
  retval->surface = GC_MALLOC(max_surfaces * sizeof(surface_t *));
  return retval;
}

scene_t *add_surface(scene_t *scene, surface_t *surface)
{
  scene->surface[scene->n_surfaces++] = surface;
  return scene;
}

void render(scene_t *scene)
{
  rgb_t c = scene->background_color;
  glClearColor(c.red, c.green, c.blue, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void test_clear_buffer(CuTest *tc)
{
  scene_t *scene = make_scene(make_rgb(0.75f, 0.25f, 0.125f), 1);
  render(scene);
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
  scene_t *scene = make_scene(black, 1);
  CuAssertIntEquals(tc, 0, scene->n_surfaces);
  scene_t *retval = add_surface(scene, add_vertex(make_surface(4), make_vertex(2, 3, 5)));
  CuAssertIntEquals(tc, 1, scene->n_surfaces);
  CuAssertDblEquals(tc, 5, scene->surface[0]->vertex[0].z, 1e-6);
  CuAssertPtrEquals(tc, scene, retval);
}

CuSuite *opengl_suite(void)
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_rgb);
  SUITE_ADD_TEST(suite, test_vertex);
  SUITE_ADD_TEST(suite, test_add_vertex);
  SUITE_ADD_TEST(suite, test_clear_buffer);
  SUITE_ADD_TEST(suite, test_add_surface);
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
