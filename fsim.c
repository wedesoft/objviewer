#define GLEW_STATIC

#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

const char *vertexShader = "#version 320 es\n\
precision highp float;\n\
layout(location = 0) in vec3 vertexPosition_modelspace;\n\
out gl_PerVertex { vec4 gl_Position; };\n\
void main(){\n\
    gl_Position.xyz = vertexPosition_modelspace;\n\
    gl_Position.w = 1.0;\n\
}";

const char *fragmentShader = "#version 320 es\n\
precision highp float;\n\
out vec3 color;\n\
void main()\n\
{\n\
	color = vec3(1,0,0);\n\
}";

GLuint vao;
GLuint vbo;
GLuint program;


void onDisplay(void)
{
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(program);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);

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

  glewExperimental = 1;
  glewInit();

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLint result = GL_FALSE;
  int info;

  GLuint vid = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vid, 1, &vertexShader, NULL);
  glCompileShader(vid);
  glGetShaderiv(vid, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vid, GL_INFO_LOG_LENGTH, &info);
  if (info > 0) {
    char buffer[65535];
    glGetShaderInfoLog(vid, info, NULL, &buffer[0]);
    printf("%s\n", buffer);
  };

  GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fid, 1, &fragmentShader, NULL);
  glCompileShader(fid);
  glGetShaderiv(fid, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fid, GL_INFO_LOG_LENGTH, &info);
  if (info > 0) {
    char buffer[65535];
    glGetShaderInfoLog(fid, info, NULL, &buffer[0]);
    printf("%s\n", buffer);
  };

  program = glCreateProgram();
  glAttachShader(program, vid);
  glAttachShader(program, fid);
  glLinkProgram(program);
  glGetShaderiv(program, GL_LINK_STATUS, &result);
  glGetShaderiv(program, GL_INFO_LOG_LENGTH, &info);
  if (info > 0) {
    char buffer[65535];
    glGetShaderInfoLog(program, info, NULL, &buffer[0]);
    printf("%s\n", buffer);
  };

  glDetachShader(program, vid);
  glDetachShader(program, fid);

  glDeleteShader(vid);
  glDeleteShader(fid);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glutDisplayFunc(onDisplay);
  glutMainLoop();

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(program);
  return 0;
}
