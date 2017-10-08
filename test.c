#include <stdio.h>
#include <GL/glut.h>
#include "CuTest.h"

typedef struct {
  GLfloat background_color[3];
} scene_t;

void set_color(GLfloat color[], GLfloat red, GLfloat green, GLfloat blue)
{
  color[0] = red;
  color[1] = green;
  color[2] = blue;
}

void render(scene_t *scene)
{
  GLfloat *bg = &scene->background_color[0];
  glClearColor(bg[0], bg[1], bg[2], 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void test_clear_buffer(CuTest *tc)
{
  scene_t scene;
  set_color(scene.background_color, 0.5f, 0.25f, 0.125f);
  render(&scene);
  // glFlush();
  GLubyte pixel[4];
  glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
  CuAssertIntEquals(tc, 128, pixel[0]);
  CuAssertIntEquals(tc,  64, pixel[1]);
  CuAssertIntEquals(tc,  32, pixel[2]);
}

CuSuite *opengl_suite(void)
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_clear_buffer);
  return suite;
}

int main(int argc, char *argv[])
{
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
