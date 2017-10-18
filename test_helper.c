#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <gc.h>
#include "test_helper.h"


int width = 32;
int height = 20;
char opengl_ready = 0;

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

void* test_setup_gl(const MunitParameter params[], void* user_data)
{
  if (!opengl_ready) {
    int argc = 0;
    char **argv = NULL;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("test");
    glewExperimental = 1;
    glewInit();
    opengl_ready = 1;
  };
  return NULL;
}
