#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <gc.h>
#include "test_helper.h"


int width = 32;
int height = 20;

void write_ppm(const char *file_name, int width, int height, unsigned char *data)
{
  FILE *f = fopen(file_name, "w");
  fprintf(f, "P3\n%d %d\n255\n", width, height);
  int i;
  for (i=0; i<height * width; i++) {
    fprintf(f, "%d %d %d\n", data[0], data[1], data[2]);
    data += 4;
  };
  fclose(f);
}

unsigned char *read_pixels(void)
{
  unsigned char *retval = GC_MALLOC_ATOMIC(width * height * 4);
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, retval);
  return retval;
}

void* test_setup_gc(const MunitParameter params[], void* user_data)
{
  GC_INIT();
}

void test_teardown_gc(void *fixture)
{
  GC_gcollect();
}

void* test_setup_gl(const MunitParameter params[], void* user_data)
{
  test_setup_gc(params, user_data);
  int argc = 0;
  char **argv = NULL;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(width, height);
  glutCreateWindow("test");
  glewExperimental = 1;
  glewInit();
  return NULL;
}

void test_teardown_gl(void *fixture)
{
  glFinish();
  test_teardown_gc(fixture);
}
