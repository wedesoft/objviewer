#include <gc.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "object.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif


int width = 320;
int height = 240;

object_t *object;
program_t *program;

void projection()
{
  float d = 1 / tan(90 / 2 * M_PI / 180);
  float d2 = d * width / height;
  float n = 0.1;
  float f = 100;
  float a = (n + f) / (n - f);
  float b = 2 * n * f / (n - f);
  float columns[4][4] = {{d, 0, 0, 0}, {0, d2, 0, 0}, {0, 0, a, -1}, {0, 0, b, 0}};
  glUniformMatrix4fv(glGetUniformLocation(program->program, "projection"), 1, GL_FALSE, &columns[0][0]);
}

void transform(float distance)
{
  float translation[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, -distance, 1}};
  glUniformMatrix4fv(glGetUniformLocation(program->program, "translation"), 1, GL_FALSE, &translation[0][0]);
}

void onResize(int w, int h)
{
  width = w; height = h;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void onDisplay(void)
{
  glUseProgram(program->program);
  transform(2);
  projection();
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
  glewExperimental = 1;
  glewInit();
  glEnable(GL_DEPTH_TEST);

  surface_t *surface = make_surface(20, 6);
  add_vertex(surface, make_vertex(-0.5f, -0.5f, 0.0f));
  add_texture_coordinate(surface, make_texture_coordinate(0.0f, 0.0f));
  add_vertex(surface, make_vertex( 0.5f, -0.5f, 0.0f));
  add_texture_coordinate(surface, make_texture_coordinate(1.0f, 0.0f));
  add_vertex(surface, make_vertex(-0.5f,  0.5f, 0.0f));
  add_texture_coordinate(surface, make_texture_coordinate(0.0f, 1.0f));
  add_vertex(surface, make_vertex( 0.5f,  0.5f, 0.0f));
  add_texture_coordinate(surface, make_texture_coordinate(1.0f, 1.0f));
  build_facet(surface, 0, 0);
  build_facet(surface, 1, 1);
  build_facet(surface, 2, 3);
  build_facet(surface, 3, 2);
  program = make_program("vertex.glsl", "fragment.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface, 1);
  setup_vertex_attribute_pointer(vertex_array_object, "point"   , 3, 5);
  setup_vertex_attribute_pointer(vertex_array_object, "texcoord", 2, 5);
  add_texture(vertex_array_object, program, make_texture("tex"), read_image("colors.png"));
  object = make_object(make_rgb(0, 0, 0), 1);
  add_vertex_array_object(object, vertex_array_object);

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);
  glutMainLoop();
  return 0;
}
