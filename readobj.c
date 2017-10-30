// Small example drawing a tetraeder using this library
#include <gc.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "fsim/object.h"
#include "fsim/projection.h"


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

  surface_t *surface = make_surface();
  add_vertex_data(surface, 3,  0.5f,  0.5f, -1.5f);
  add_vertex_data(surface, 3, -0.5f,  0.5f, -2.5f);
  add_vertex_data(surface, 3, -0.5f, -0.5f, -1.5f);
  add_triangle(surface, 1, 2, 0);
  program = make_program("projection.glsl", "white.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 3);
  object = make_object("triangle");
  add_vertex_array_object(object, vertex_array_object);

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);
  glutMainLoop();
  return 0;
}
