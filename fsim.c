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
} object_t;

object_t *make_object(int max_vertices, int max_indices)
{
  object_t *retval = GC_MALLOC(sizeof(object_t));
  retval->n_vertices = 0;
  retval->vertex = GC_MALLOC(max_vertices * sizeof(vertex_t));
  retval->n_indices = 0;
  retval->vertex_index = GC_MALLOC(max_indices * sizeof(int));
  return retval;
}

object_t *add_vertex(object_t *object, vertex_t vertex)
{
  object->vertex[object->n_vertices++] = vertex;
  return object;
}

void test_add_vertex(CuTest *tc)
{
  object_t *object = make_object(3, 3);
  CuAssertIntEquals(tc, 0, object->n_vertices);
  add_vertex(object, make_vertex(2.5f, 3.5f, 5.5f));
  CuAssertIntEquals(tc, 1, object->n_vertices);
  CuAssertDblEquals(tc, 2.5, object->vertex[0].x, 1e-6);
  object_t *retval = add_vertex(object, make_vertex(1.5f, 4.5f, 7.5f));
  CuAssertDblEquals(tc, 1.5, object->vertex[1].x, 1e-6);
  CuAssertPtrEquals(tc, object, retval);
}

void extend_facet(object_t *object, int number, int vertex_index)
{
  int n = object->n_indices;
  if (number < 3) {
    object->vertex_index[n] = vertex_index;
    object->n_indices = n + 1;
  } else {
    extend_facet(object, 0, object->vertex_index[n - 3]);
    extend_facet(object, 1, object->vertex_index[n - 1]);
    extend_facet(object, 2, vertex_index);
  };
}

void test_add_triangle(CuTest *tc)
{
  object_t *object = make_object(3, 3);
  int i;
  for (i=0; i<3; i++)
    add_vertex(object, make_vertex(i % 2, 0, i / 2));
  CuAssertIntEquals(tc, 0, object->n_indices);
  extend_facet(object, 0, 2);
  extend_facet(object, 1, 0);
  extend_facet(object, 2, 1);
  CuAssertIntEquals(tc, 3, object->n_indices);
  CuAssertIntEquals(tc, 2, object->vertex_index[0]);
  CuAssertIntEquals(tc, 0, object->vertex_index[1]);
  CuAssertIntEquals(tc, 1, object->vertex_index[2]);
}

void test_add_square(CuTest *tc)
{
  object_t *object = make_object(4, 6);
  int i;
  for (i=0; i<4; i++)
    add_vertex(object, make_vertex(i % 2, 0, i / 2));
  extend_facet(object, 0, 2);
  extend_facet(object, 1, 0);
  extend_facet(object, 2, 1);
  extend_facet(object, 3, 3);
  CuAssertIntEquals(tc, 6, object->n_indices);
  CuAssertIntEquals(tc, 2, object->vertex_index[3]);
  CuAssertIntEquals(tc, 1, object->vertex_index[4]);
  CuAssertIntEquals(tc, 3, object->vertex_index[5]);
}

void test_add_pentagon(CuTest *tc)
{
  object_t *object = make_object(5, 9);
  int i;
  for (i=0; i<4; i++)
    add_vertex(object, make_vertex(i % 2, 0, i / 2));
  add_vertex(object, make_vertex(0.5, 0, 1.5));
  extend_facet(object, 0, 0);
  extend_facet(object, 1, 1);
  extend_facet(object, 2, 3);
  extend_facet(object, 3, 4);
  extend_facet(object, 4, 2);
  CuAssertIntEquals(tc, 9, object->n_indices);
  CuAssertIntEquals(tc, 0, object->vertex_index[6]);
  CuAssertIntEquals(tc, 4, object->vertex_index[7]);
  CuAssertIntEquals(tc, 2, object->vertex_index[8]);
}

typedef struct {
  rgb_t background_color;
  int n_objects;
  object_t **object;
} scene_t;

scene_t *make_scene(rgb_t background_color, int max_objects)
{
  scene_t *retval = GC_MALLOC(sizeof(scene_t));
  retval->background_color = background_color;
  retval->n_objects = 0;
  retval->object = GC_MALLOC(max_objects * sizeof(object_t *));
  return retval;
}

scene_t *add_object(scene_t *scene, object_t *object)
{
  scene->object[scene->n_objects++] = object;
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

void test_add_object(CuTest *tc)
{
  rgb_t black = make_rgb(0.0f, 0.0f, 0.0f);
  scene_t *scene = make_scene(black, 1);
  CuAssertIntEquals(tc, 0, scene->n_objects);
  scene_t *retval = add_object(scene, add_vertex(make_object(4, 1), make_vertex(2, 3, 5)));
  CuAssertIntEquals(tc, 1, scene->n_objects);
  CuAssertDblEquals(tc, 5, scene->object[0]->vertex[0].z, 1e-6);
  CuAssertPtrEquals(tc, scene, retval);
}

CuSuite *opengl_suite(void)
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_rgb);
  SUITE_ADD_TEST(suite, test_vertex);
  SUITE_ADD_TEST(suite, test_add_vertex);
  SUITE_ADD_TEST(suite, test_clear_buffer);
  SUITE_ADD_TEST(suite, test_add_object);
  SUITE_ADD_TEST(suite, test_add_triangle);
  SUITE_ADD_TEST(suite, test_add_square);
  SUITE_ADD_TEST(suite, test_add_pentagon);
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
