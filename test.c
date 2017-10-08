#include <stdio.h>
#include <GL/glut.h>
#include "CuTest.h"

typedef struct {
  GLfloat red;
  GLfloat green;
  GLfloat blue;
} rgb_t;

rgb_t rgb(GLfloat red, GLfloat green, GLfloat blue)
{
  rgb_t retval;
  retval.red   = red;
  retval.green = green;
  retval.blue  = blue;
  return retval;
}

typedef struct {
  rgb_t background_color;
} scene_t;

void test_rgb(CuTest *tc)
{
  CuAssertDblEquals(tc, 0.50f, rgb(0.5f, 0.75f, 0.25f).red  , 1e-6);
  CuAssertDblEquals(tc, 0.75f, rgb(0.5f, 0.75f, 0.25f).green, 1e-6);
  CuAssertDblEquals(tc, 0.25f, rgb(0.5f, 0.75f, 0.25f).blue , 1e-6);
}

void render(scene_t *scene)
{
  rgb_t bg = scene->background_color;
  glClearColor(bg.red, bg.green, bg.blue, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void test_clear_buffer(CuTest *tc)
{
  scene_t scene;
  scene.background_color = rgb(0.5f, 0.25f, 0.125f);
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
  SUITE_ADD_TEST(suite, test_rgb);
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
