// Small example drawing a tetraeder using this library
#include <gc.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "fsim/object.h"
#include "fsim/projection.h"
#include "fsim/parser.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

int width = 320;
int height = 240;

object_t *object;
program_t *program;

void onResize(int w, int h)
{
  width = w; height = h;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void onDisplay(void)
{
  uniform_matrix(program, "projection", projection(width, height, 0.1, 100, 90.0));
  glUseProgram(program->program);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  render(object);
  glutSwapBuffers();
}

int main(int argc, char **argv)
{
  GC_INIT();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("triangle");
  glewExperimental = GL_TRUE;
  glewInit();
  glEnable(GL_DEPTH_TEST);

  program = make_program("projection.glsl", "white.glsl");
  object = parse_string(program, "o triangle\nv 0.5 0.5 -1.5\nv -0.5 0.5 -2.5\nv -0.5 -0.5 -1.5\ns off\nf 2 3 1\n");
  vertex_array_object_t *vao = get_pointer(object->vertex_array_object)[0];
  setup_vertex_attribute_pointer(vao, "point", 3, 3);

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);
  glutMainLoop();
  return 0;
}
