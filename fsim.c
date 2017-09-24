#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>


void onDisplay(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableClientState(GL_VERTEX_ARRAY);

  glutSwapBuffers();
}

GLfloat vertices[] = {
   0.0f,  0.5f, 1.0f,
   0.5f, -0.5f, 1.0f,
  -0.5f, -0.5f, 1.0f
};

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(320, 240);
  glutCreateWindow("Triangle");

  glewInit();

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  GLuint vbo;
  glGenBuffersARB(1, &vbo);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices), 0, GL_STATIC_DRAW_ARB);
  glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(vertices), vertices);

  glutDisplayFunc(onDisplay);
  glutMainLoop();

  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
  glDeleteBuffersARB(1, &vbo);
  return 0;
}
