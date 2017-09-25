#define GLEW_STATIC

#include <math.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

const char *vertexSource = "#version 300 es\n\
in mediump vec3 point;\n\
uniform mat4 model;\n\
void main()\n\
{\n\
  gl_Position = model * vec4(point, 1);\n\
}";

const char *fragmentSource = "#version 300 es\n\
out mediump vec3 color;\n\
void main()\n\
{\n\
	color = vec3(1,0,0);\n\
}";

GLuint vao;
GLuint vbo;
GLuint program;

float angle = 0;


void onDisplay(void)
{
  float matrix[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(program);
  float sin_angle = sin(angle * M_PI / 180);
  float cos_angle = cos(angle * M_PI / 180);
  matrix[0] = cos_angle; matrix[5] = cos_angle;
  matrix[1] = -sin_angle; matrix[4] = sin_angle;
  glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, matrix);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);

  glutSwapBuffers();
}

void onResize(int width, int height)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glOrtho(-1, 1, -1, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
}

void onKey(int key, int x, int y)
{
  switch (key) {
  case GLUT_KEY_LEFT:
    angle -= 1;
    break;
  case GLUT_KEY_RIGHT:
    angle += 1;
    break;
  default:
    return;
  };
  glutPostRedisplay();
}

void showErrors(const char *step, GLuint context)
{
  GLint result = GL_FALSE;
  int infoLength = 0;
  glGetShaderiv(context, GL_COMPILE_STATUS, &result);
  glGetShaderiv(context, GL_INFO_LOG_LENGTH, &infoLength);
  if (result == GL_FALSE && infoLength > 0) {
    char *buffer = malloc(infoLength);
    glGetShaderInfoLog(context, infoLength, NULL, buffer);
    fprintf(stderr, "%s: %s\n", step, buffer);
    free(buffer);
  };
}

GLfloat vertices[] = {
   0.5f,  0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f
};

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(320, 320);
  glutCreateWindow("Triangle");

  glewExperimental = 1;
  glewInit();

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  showErrors("Vertex shader", vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  showErrors("Fragment shader", fragmentShader);

  program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  showErrors("Link stage", program);

  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);
  glutSpecialFunc(onKey);
  glutMainLoop();

  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(program);
  return 0;
}
