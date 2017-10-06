#include <string.h>
#include <stdio.h>
#include <GL/glut.h>

void printError(const char *context)
{
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    fprintf(stderr, "%s: %s\n", context, gluErrorString(error));
  };
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA);
  glutInitWindowSize(32, 20);
  glutCreateWindow("test");
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  GLubyte pixel[4];
  memset(pixel, 0, sizeof(pixel));
  glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
  printf("%u %u %u %u\n", pixel[0], pixel[1], pixel[2], pixel[3]);
  return 0;
}
