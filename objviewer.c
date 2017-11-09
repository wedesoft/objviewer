// Small example loading and drawing a WaveFront Object File using this library
#include <stdio.h>
#include <math.h>
#include <gc.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "fsim/object.h"
#include "fsim/program.h"
#include "fsim/vertex_array_object.h"
#include "fsim/projection.h"
#include "fsim/parser.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

int width = 320;
int height = 240;

float yaw = 0;
float pitch = 0;
float distance = 200;
float scale = 0.01;
float level = 0;

object_t *object;
program_t *program;
list_t *list;

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
  float translation_columns[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, level, -distance * scale, 1}};
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
  uniform_matrix(program, "projection", projection(width, height, 0.1, 10000, 90.0));
  glUseProgram(program->program);
  transform();
  light();
  glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  render(list);
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
    distance += 3;
    break;
  case GLUT_KEY_PAGE_DOWN:
    distance -= 3;
    break;
  case GLUT_KEY_HOME:
    level -= 3;
    break;
  case GLUT_KEY_END:
    level += 3;
    break;
  default:
    return;
  };
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  if (argc == 1) {
    fprintf(stderr, "Syntax: objviewer <object file>\n");
    return 1;
  };

  object = parse_file(argv[1]);

  if (!object) {
    fprintf(stderr, "Error reading object file %s\n", argv[1]);
    return 1;
  };

  GC_INIT();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("objviewer");
  glewExperimental = GL_TRUE;
  glewInit();
  glEnable(GL_DEPTH_TEST);

  program = make_program("vertex.glsl", "fragment.glsl");
  list = make_vertex_array_object_list(program, object);

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);
  glutSpecialFunc(onKey);
  glutMainLoop();

  return 0;
}
