#include <gc.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "object.h"


int width = 320;
int height = 240;

object_t *object;

void onResize(int w, int h)
{
  width = w; height = h;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void onDisplay(void)
{
  render(object);
  glutSwapBuffers();
}

int main(int argc, char **argv)
{
  GC_INIT();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("tetraeder");

  object = make_object(make_rgb(0.1f, 0.1f, 0.1f), 1);

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);

  glewExperimental = 1;
  glewInit();

  glutMainLoop();
  return 0;
}
