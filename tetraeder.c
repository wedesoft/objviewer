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

float yaw = 0;
float pitch = 0;
float distance = 2;

object_t *object;
program_t *program;

void transform(void)
{
  float sin_yaw = sin(yaw * M_PI / 180);
  float cos_yaw = cos(yaw * M_PI / 180);
  float yaw_columns[4][4] = {{cos_yaw, 0, sin_yaw, 0}, {0, 1, 0, 0}, {-sin_yaw, 0, cos_yaw, 0}, {0, 0, 0, 1}};
  glUniformMatrix4fv(glGetUniformLocation(program->program, "yaw"), 1, GL_FALSE, &yaw_columns[0][0]);
  float sin_pitch = sin(pitch * M_PI / 180);
  float cos_pitch = cos(pitch * M_PI / 180);
  float pitch_columns[4][4] = {{1, 0, 0, 0}, {0, cos_pitch, -sin_pitch, 0}, {0, sin_pitch, cos_pitch, 0}, {0, 0, 0, 1}};
  glUniformMatrix4fv(glGetUniformLocation(program->program, "pitch"), 1, GL_FALSE, &pitch_columns[0][0]);
  float translation_columns[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, -distance, 1}};
  glUniformMatrix4fv(glGetUniformLocation(program->program, "translation"), 1, GL_FALSE, &translation_columns[0][0]);
}

void light() {
  float vector[] = {0.37139068f,  0.74278135f,  0.55708601f};
  glUniform3fv(glGetUniformLocation(program->program, "ray"), 1, &vector[0]);
}

void onResize(int w, int h)
{
  width = w; height = h;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void onDisplay(void)
{
  uniform_matrix(program, "projection", projection(width, height, 0.1, 100, 90.0));
  glUseProgram(program->program);
  transform();
  light();
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  render(object);
  glutSwapBuffers();
}

void onKey(int key, int x, int y)
{
  switch (key) {
  case GLUT_KEY_LEFT:
    yaw -= 2;
    break;
  case GLUT_KEY_RIGHT:
    yaw += 2;
    break;
  case GLUT_KEY_UP:
    pitch -= 2;
    break;
  case GLUT_KEY_DOWN:
    pitch += 2;
    break;
  case GLUT_KEY_PAGE_UP:
    distance += 0.05;
    break;
  case GLUT_KEY_PAGE_DOWN:
    distance -= 0.05;
    break;
  case GLUT_KEY_HOME:
    yaw = 0;
    pitch = 0;
    distance = 2;
    break;
  default:
    return;
  };
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  GC_INIT();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("tetraeder");
  glewExperimental = GL_TRUE;
  glewInit();
  glEnable(GL_DEPTH_TEST);

  surface_t *surface = make_surface();
  add_vertex_data(surface, 8,  0.5f,  0.5f,  0.5f, 16.0f, 16.0f, -0.577350269f,  0.577350269f,  0.577350269f);
  add_vertex_data(surface, 8, -0.5f,  0.5f, -0.5f,  0.0f, 16.0f, -0.577350269f, -0.577350269f, -0.577350269f);
  add_vertex_data(surface, 8, -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.577350269f, -0.577350269f,  0.577350269f);
  add_vertex_data(surface, 8,  0.5f, -0.5f, -0.5f, 16.0f,  0.0f,  0.577350269f,  0.577350269f, -0.577350269f);
  add_polygon(surface, 3, 1, 2, 0);
  add_polygon(surface, 3, 3, 2, 1);
  add_polygon(surface, 3, 3, 0, 2);
  add_polygon(surface, 3, 1, 0, 3);
  program = make_program("vertex.glsl", "fragment.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point"   , 3, 8);
  setup_vertex_attribute_pointer(vertex_array_object, "texcoord", 2, 8);
  setup_vertex_attribute_pointer(vertex_array_object, "vector"  , 3, 8);
  add_texture(vertex_array_object, program, make_texture("tex"), read_image("colors.png"));
  object = make_object("tetraeder");
  add_vertex_array_object(object, vertex_array_object);

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);
  glutSpecialFunc(onKey);
  glutMainLoop();
  return 0;
}
