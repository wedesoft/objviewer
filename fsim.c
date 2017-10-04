#define GLEW_STATIC

#include <math.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

const char *vertexSource = "#version 300 es\n\
layout(location = 0) in mediump vec3 point;\n\
layout(location = 1) in mediump vec2 texcoord;\n\
layout(location = 2) in mediump vec3 normal;\n\
uniform mat4 yaw;\n\
uniform mat4 pitch;\n\
uniform mat4 translation;\n\
uniform mat4 projection;\n\
out mediump vec2 UV;\n\
flat out mediump vec3 eyeNormal;\n\
void main()\n\
{\n\
  mat4 model = translation * yaw * pitch;\n\
  gl_Position = projection * model * vec4(point, 1);\n\
  UV = texcoord;\n\
  eyeNormal = (model * vec4(normal, 0)).xyz;\n\
}";

const char *fragmentSource = "#version 300 es\n\
in mediump vec2 UV;\n\
flat in mediump vec3 eyeNormal;\n\
out mediump vec3 fragColor;\n\
uniform sampler2D tex;\n\
void main()\n\
{\n\
  mediump vec3 light = normalize(vec3(3.0, -1.0, -4));\n\
  mediump float diffuse = max(0.0, dot(eyeNormal, light));\n\
  fragColor = texture(tex, UV).rgb * (0.1 + 0.9 * diffuse);\n\
}";

GLuint vao;
GLuint vbo;
GLuint idx;
GLuint program;
GLuint tex;
int width = 320;
int height = 240;

float yaw = 0;
float pitch = 0;
float distance = 2;

void projection(const char *target)
{
  float d = 1 / tan(90 / 2 * M_PI / 180);
  float d2 = d * width / height;
  float n = 0.1;
  float f = 100;
  float a = (n + f) / (n - f);
  float b = 2 * n * f / (n - f);
  float columns[4][4] = {{d, 0, 0, 0}, {0, d2, 0, 0}, {0, 0, a, -1}, {0, 0, b, 0}};
  glUniformMatrix4fv(glGetUniformLocation(program, target), 1, GL_FALSE, &columns[0][0]);
}

void transform(float yaw, float pitch, float distance)
{
  float sin_yaw = sin(yaw * M_PI / 180);
  float cos_yaw = cos(yaw * M_PI / 180);
  float yawColumns[4][4] = {{cos_yaw, 0, sin_yaw, 0}, {0, 1, 0, 0}, {-sin_yaw, 0, cos_yaw, 0}, {0, 0, 0, 1}};
  glUniformMatrix4fv(glGetUniformLocation(program, "yaw"), 1, GL_FALSE, &yawColumns[0][0]);
  float sin_pitch = sin(pitch * M_PI / 180);
  float cos_pitch = cos(pitch * M_PI / 180);
  float pitchColumns[4][4] = {{1, 0, 0, 0}, {0, cos_pitch, -sin_pitch, 0}, {0, sin_pitch, cos_pitch, 0}, {0, 0, 0, 1}};
  glUniformMatrix4fv(glGetUniformLocation(program, "pitch"), 1, GL_FALSE, &pitchColumns[0][0]);
  float translationColumns[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, -distance, 1}};
  glUniformMatrix4fv(glGetUniformLocation(program, "translation"), 1, GL_FALSE, &translationColumns[0][0]);
}

void onDisplay(void)
{
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(program);
  projection("projection");
  transform(yaw, pitch, distance);
  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void *)0);

  glutSwapBuffers();
}

void onResize(int w, int h)
{
  width = w; height = h;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
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
  default:
    return;
  };
  glutPostRedisplay();
}

void printError(const char *context)
{
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    fprintf(stderr, "%s: %s\n", context, gluErrorString(error));
  };
}

void printStatus(const char *step, GLuint context, GLuint status)
{
  GLint result = GL_FALSE;
  glGetShaderiv(context, status, &result);
  if (result == GL_FALSE) {
    char buffer[1024];
    if (status == GL_COMPILE_STATUS)
      glGetShaderInfoLog(context, 1024, NULL, buffer);
    else
      glGetProgramInfoLog(context, 1024, NULL, buffer);
    if (buffer[0])
      fprintf(stderr, "%s: %s\n", step, buffer);
  };
}

void printCompileStatus(const char *step, GLuint context)
{
  printStatus(step, context, GL_COMPILE_STATUS);
}

void printLinkStatus(const char *step, GLuint context)
{
  printStatus(step, context, GL_LINK_STATUS);
}

GLfloat na = 1.0f / 3.0f;
GLfloat nb = 2.0f / 3.0f;

GLfloat vertices[] = {
   0.5f,  0.5f,  0.5f, 16.0f, 16.0f,  0.57735027f, -0.57735027f, -0.57735027f,
  -0.5f,  0.5f, -0.5f,  0.0f, 16.0f,  0.57735027f,  0.57735027f,  0.57735027f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -0.57735027f,  0.57735027f, -0.57735027f,
   0.5f, -0.5f, -0.5f, 16.0f,  0.0f, -0.57735027f, -0.57735027f,  0.57735027f
};

unsigned int indices[] = {
  1, 2, 0,
  3, 2, 1,
  3, 0, 2,
  1, 0, 3
};

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glutInitWindowSize(width, height);
  glutCreateWindow("tetraeder");

  glewExperimental = 1;
  glewInit();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &idx);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  printCompileStatus("Vertex shader", vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  printCompileStatus("Fragment shader", fragmentShader);

  program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  printLinkStatus("Shader program", program);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(glGetAttribLocation(program, "point"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glVertexAttribPointer(glGetAttribLocation(program, "texcoord"), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glVertexAttribPointer(glGetAttribLocation(program, "normal"), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));

  glGenTextures(1, &tex);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(glGetUniformLocation(program, "tex"), 0);
  float pixels[] = {
    0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
  };
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_BGR, GL_FLOAT, pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
    GLfloat max_anisotropy;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
  };
  glGenerateMipmap(GL_TEXTURE_2D);

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);
  glutSpecialFunc(onKey);
  glutMainLoop();

  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &tex);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &idx);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vbo);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &vao);

  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);
  glDeleteProgram(program);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return 0;
}
