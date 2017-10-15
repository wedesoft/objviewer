#define GLEW_STATIC
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <magick/MagickCore.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <gc.h>
#include "CuTest.h"


int width = 32;
int height = 20;


typedef struct {
  GLfloat red;
  GLfloat green;
  GLfloat blue;
} rgb_t;

rgb_t make_rgb(GLfloat red, GLfloat green, GLfloat blue)
{
  rgb_t retval;
  retval.red   = red;
  retval.green = green;
  retval.blue  = blue;
  return retval;
}

void test_rgb(CuTest *tc)
{
  rgb_t c = make_rgb(0.5f, 0.75f, 0.25f);
  CuAssertDblEquals(tc, 0.50, c.red  , 1e-6);
  CuAssertDblEquals(tc, 0.75, c.green, 1e-6);
  CuAssertDblEquals(tc, 0.25, c.blue , 1e-6);
}

typedef struct {
  GLfloat x;
  GLfloat y;
  GLfloat z;
} vertex_t;

vertex_t make_vertex(GLfloat x, GLfloat y, GLfloat z)
{
  vertex_t retval;
  retval.x = x;
  retval.y = y;
  retval.z = z;
  return retval;
}

void test_vertex(CuTest *tc)
{
  vertex_t v = make_vertex(2.0f, 3.0f, 5.0f);
  CuAssertDblEquals(tc, 2.0f, v.x, 1e-6f);
  CuAssertDblEquals(tc, 3.0f, v.y, 1e-6f);
  CuAssertDblEquals(tc, 5.0f, v.z, 1e-6f);
}

typedef struct {
  GLfloat x;
  GLfloat y;
  GLfloat z;
} normal_t;

normal_t make_normal(GLfloat x, GLfloat y, GLfloat z)
{
  normal_t retval;
  retval.x = x;
  retval.y = y;
  retval.z = z;
  return retval;
}

void test_normal(CuTest *tc)
{
  normal_t n = make_normal(0.36f, 0.48f, 0.8f);
  CuAssertDblEquals(tc, 0.36f, n.x, 1e-6f);
  CuAssertDblEquals(tc, 0.48f, n.y, 1e-6f);
  CuAssertDblEquals(tc, 0.80f, n.z, 1e-6f);
}

typedef struct
{
  GLuint shader;
} shader_t;

typedef struct {
  shader_t *vertex_shader;
  shader_t *fragment_shader;
  GLuint program;
  int n_attributes;
  long attribute_pointer;
} program_t;

typedef struct {
  program_t *program;
  GLuint vertex_array_object;
  GLuint vertex_buffer_object;
  GLuint element_buffer_object;
} vertex_array_object_t;

typedef struct {
  int n_array;
  GLfloat *array;
  int n_indices;
  int *vertex_index;
} surface_t;

surface_t *make_surface(int max_array, int max_indices)
{
  surface_t *retval = GC_MALLOC(sizeof(surface_t));
  retval->n_array = 0;
  retval->array = GC_MALLOC_ATOMIC(max_array * sizeof(GLfloat));
  retval->n_indices = 0;
  retval->vertex_index = GC_MALLOC_ATOMIC(max_indices * sizeof(int));
  return retval;
}

surface_t *add_vertex(surface_t *surface, vertex_t vertex)
{
  surface->array[surface->n_array++] = vertex.x;
  surface->array[surface->n_array++] = vertex.y;
  surface->array[surface->n_array++] = vertex.z;
  return surface;
}

int size_of_array(surface_t *surface)
{
  return surface->n_array * sizeof(GLfloat);
}

void test_empty_surface(CuTest *tc)
{
  surface_t *surface = make_surface(9, 3);
  CuAssertIntEquals(tc, 0, surface->n_array);
}

void test_add_one_vertex(CuTest *tc)
{
  surface_t *surface = make_surface(9, 3);
  surface_t *retval = add_vertex(surface, make_vertex(2.5f, 3.5f, 5.5f));
  CuAssertIntEquals(tc, 3, surface->n_array);
  CuAssertDblEquals(tc, 2.5f, surface->array[0], 1e-6f);
  CuAssertDblEquals(tc, 3.5f, surface->array[1], 1e-6f);
  CuAssertDblEquals(tc, 5.5f, surface->array[2], 1e-6f);
  CuAssertPtrEquals(tc, surface, retval);
}

void test_add_two_vertices(CuTest *tc)
{
  surface_t *surface = make_surface(9, 3);
  add_vertex(surface, make_vertex(2.5f, 3.5f, 5.5f));
  add_vertex(surface, make_vertex(1.5f, 4.5f, 7.5f));
  CuAssertDblEquals(tc, 1.5f, surface->array[3], 1e-6f);
  CuAssertDblEquals(tc, 4.5f, surface->array[4], 1e-6f);
  CuAssertDblEquals(tc, 7.5f, surface->array[5], 1e-6f);
}

surface_t *add_normal(surface_t *surface, normal_t normal)
{
  surface->array[surface->n_array++] = normal.x;
  surface->array[surface->n_array++] = normal.y;
  surface->array[surface->n_array++] = normal.z;
  return surface;
}

void test_add_normal(CuTest *tc)
{
  surface_t *surface = make_surface(9, 3);
  add_vertex(surface, make_vertex(2.5f, 3.5f, 5.5f));
  add_normal(surface, make_normal(0.36f, 0.48f, 0.8f));
  CuAssertIntEquals(tc, 6, surface->n_array);
  CuAssertDblEquals(tc, 0.36f, surface->array[3], 1e-6f);
  CuAssertDblEquals(tc, 0.48f, surface->array[4], 1e-6f);
  CuAssertDblEquals(tc, 0.80f, surface->array[5], 1e-6f);
}

void test_size_of_array(CuTest *tc)
{
  surface_t *surface = make_surface(9, 3);
  CuAssertIntEquals(tc, 0, size_of_array(surface));
  add_vertex(surface, make_vertex(2.5f, 3.5f, 5.5f));
  CuAssertIntEquals(tc, sizeof(vertex_t), size_of_array(surface));
}

void build_facet(surface_t *surface, int number, int vertex_index)
{
  int n = surface->n_indices;
  if (number < 3) {
    surface->vertex_index[n] = vertex_index;
    surface->n_indices = n + 1;
  } else {
    build_facet(surface, 0, surface->vertex_index[n - 3]);
    build_facet(surface, 1, surface->vertex_index[n - 1]);
    build_facet(surface, 2, vertex_index);
  };
}

int size_of_indices(surface_t *surface)
{
  return surface->n_indices * sizeof(int);
}

void test_no_indices(CuTest *tc)
{
  surface_t *surface = make_surface(9, 3);
  CuAssertIntEquals(tc, 0, surface->n_indices);
}

void test_add_triangle(CuTest *tc)
{
  surface_t *surface = make_surface(9, 3);
  int i;
  for (i=0; i<3; i++)
    add_vertex(surface, make_vertex(i % 2, 0, i / 2));
  build_facet(surface, 0, 2);
  build_facet(surface, 1, 0);
  build_facet(surface, 2, 1);
  CuAssertIntEquals(tc, 3, surface->n_indices);
  CuAssertIntEquals(tc, 2, surface->vertex_index[0]);
  CuAssertIntEquals(tc, 0, surface->vertex_index[1]);
  CuAssertIntEquals(tc, 1, surface->vertex_index[2]);
}

void test_add_square(CuTest *tc)
{
  surface_t *surface = make_surface(12, 6);
  int i;
  for (i=0; i<4; i++)
    add_vertex(surface, make_vertex(i % 2, 0, i / 2));
  build_facet(surface, 0, 2);
  build_facet(surface, 1, 0);
  build_facet(surface, 2, 1);
  build_facet(surface, 3, 3);
  CuAssertIntEquals(tc, 6, surface->n_indices);
  CuAssertIntEquals(tc, 2, surface->vertex_index[3]);
  CuAssertIntEquals(tc, 1, surface->vertex_index[4]);
  CuAssertIntEquals(tc, 3, surface->vertex_index[5]);
}

void test_add_pentagon(CuTest *tc)
{
  surface_t *surface = make_surface(15, 9);
  int i;
  for (i=0; i<4; i++)
    add_vertex(surface, make_vertex(i % 2, 0, i / 2));
  add_vertex(surface, make_vertex(0.5, 0, 1.5));
  build_facet(surface, 0, 0);
  build_facet(surface, 1, 1);
  build_facet(surface, 2, 3);
  build_facet(surface, 3, 4);
  build_facet(surface, 4, 2);
  CuAssertIntEquals(tc, 9, surface->n_indices);
  CuAssertIntEquals(tc, 0, surface->vertex_index[6]);
  CuAssertIntEquals(tc, 4, surface->vertex_index[7]);
  CuAssertIntEquals(tc, 2, surface->vertex_index[8]);
}

void test_size_of_indices(CuTest *tc)
{
  surface_t *surface = make_surface(9, 3);
  CuAssertIntEquals(tc, 0, size_of_indices(surface));
  add_vertex(surface, make_vertex(0, 0, 0));
  build_facet(surface, 0, 0);
  CuAssertIntEquals(tc, sizeof(int), size_of_indices(surface));
}

typedef struct {
  rgb_t background_color;
  int n_vertex_array_objects;
  vertex_array_object_t **vertex_array_object;
} object_t;

object_t *make_object(rgb_t background_color, int max_vertex_array_objects)
{
  object_t *retval = GC_MALLOC(sizeof(object_t));
  retval->background_color = background_color;
  retval->n_vertex_array_objects = 0;
  retval->vertex_array_object = GC_MALLOC(max_vertex_array_objects * sizeof(vertex_array_object_t *));
  return retval;
}

object_t *add_vertex_array_object(object_t *object, vertex_array_object_t *vertex_array_object)
{
  object->vertex_array_object[object->n_vertex_array_objects++] = vertex_array_object;
  return object;
}

void write_ppm(const char *file_name, int width, int height, unsigned char *data)
{
  FILE *f = fopen(file_name, "w");
  fprintf(f, "P3\n%d %d\n255\n", width, height);
  int i;
  for (i=0; i<height * width; i++) {
    fprintf(f, "%d %d %d\n", data[0], data[1], data[2]);
    data += 4;
  };
  fclose(f);
}

void draw_elements(vertex_array_object_t *vertex_array_object)
{
  glUseProgram(vertex_array_object->program->program);
  glBindVertexArray(vertex_array_object->vertex_array_object);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void *)0);/* TODO: use correct number of triangles */
}

void render(object_t *object)
{
  rgb_t c = object->background_color;
  glClearColor(c.red, c.green, c.blue, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  int i;
  for (i=0; i<object->n_vertex_array_objects; i++)
    draw_elements(object->vertex_array_object[i]);
}

unsigned char *read_pixels(void)
{
  unsigned char *retval = GC_MALLOC_ATOMIC(width * height * 4);
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, retval);
  return retval;
}

void test_clear_buffer(CuTest *tc)
{
  object_t *object = make_object(make_rgb(0.75f, 0.25f, 0.125f), 1);
  render(object);
  glFlush();
  unsigned char *data = read_pixels();
  write_ppm("clear_buffer.ppm", width, height, data);
  CuAssertIntEquals(tc, 191, data[0]);
  CuAssertIntEquals(tc,  64, data[1]);
  CuAssertIntEquals(tc,  32, data[2]);
}

void finalize_vertex_array_object(GC_PTR obj, GC_PTR env)
{
  vertex_array_object_t *target = (vertex_array_object_t *)obj;
  glBindVertexArray(target->vertex_array_object);
  int i;
  for (i=0; i<target->program->n_attributes; i++)
    glDisableVertexAttribArray(i);
  glBindVertexArray(target->vertex_array_object);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &target->element_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &target->vertex_buffer_object);
  glDeleteBuffers(1, &target->vertex_array_object);
}

vertex_array_object_t *make_vertex_array_object(program_t *program, surface_t *surface)
{
  vertex_array_object_t *retval = GC_MALLOC_ATOMIC(sizeof(vertex_array_object_t));
  GC_register_finalizer(retval, finalize_vertex_array_object, 0, 0, 0);
  retval->program = program;
  glGenVertexArrays(1, &retval->vertex_array_object);
  glBindVertexArray(retval->vertex_array_object);
  glGenBuffers(1, &retval->vertex_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, retval->vertex_buffer_object);
  glBufferData(GL_ARRAY_BUFFER, size_of_array(surface), surface->array, GL_STATIC_DRAW);
  glGenBuffers(1, &retval->element_buffer_object);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval->element_buffer_object);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices(surface), surface->vertex_index, GL_STATIC_DRAW);
  return retval;
}

void test_empty_object(CuTest *tc)
{
  object_t *object = make_object(make_rgb(0, 0, 0), 1);
  CuAssertIntEquals(tc, 0, object->n_vertex_array_objects);
}

void finalize_shader(GC_PTR obj, GC_PTR env)
{
  shader_t *target = (shader_t *)obj;
  if (target->shader)
    glDeleteShader(target->shader);
}

int report_status(const char *text, GLuint context, GLuint status)
{
  GLint result = GL_FALSE;
  GLint length = 0;
  glGetShaderiv(context, status, &result);
  if (result == GL_FALSE) {
    glGetShaderiv(context, GL_INFO_LOG_LENGTH, &length);
    char *info = GC_MALLOC_ATOMIC(length + 1);
    info[0] = 0;
    if (status == GL_COMPILE_STATUS)
      glGetShaderInfoLog(context, length, NULL, info);
    else
      glGetProgramInfoLog(context, length, NULL, info);
    if (info[0])
      fprintf(stderr, "%s: %s\n", text, info);
    else
      result = GL_TRUE;
  };
  return result;
}

int report_compile_status(const char *file_name, GLuint context)
{
  return report_status(file_name, context, GL_COMPILE_STATUS);
}

int report_link_status(GLuint context)
{
  return report_status("link shader program", context, GL_LINK_STATUS);
}

shader_t *make_shader(GLenum shader_type, const char *file_name)
{
  shader_t *retval = GC_MALLOC_ATOMIC(sizeof(shader_t));
  GC_register_finalizer(retval, finalize_shader, 0, 0, 0);
  retval->shader = 0;
  FILE *f = fopen(file_name, "r");
  if (f) {
    struct stat st;
    stat(file_name, &st);
    char *source = GC_MALLOC_ATOMIC(st.st_size + 1);
    fread(source, st.st_size, 1, f);
    source[st.st_size] = '\0';
    fclose(f);
    retval->shader = glCreateShader(shader_type);
    const GLchar *shader_source = source;
    glShaderSource(retval->shader, 1, &shader_source, NULL);
    glCompileShader(retval->shader);
    if (!report_compile_status(file_name, retval->shader))
      retval = NULL;
  } else
    retval = NULL;
  return retval;
}

void finalize_program(GC_PTR obj, GC_PTR env)
{
  program_t *target = (program_t *)obj;
  if (target->program) {
    if (target->vertex_shader)
      glDetachShader(target->program, target->vertex_shader->shader);
    if (target->fragment_shader)
      glDetachShader(target->program, target->fragment_shader->shader);
    glDeleteProgram(target->program);
  };
}

program_t *make_program(const char *vertex_shader_file_name, const char *fragment_shader_file_name)
{
  program_t *retval = GC_MALLOC(sizeof(program_t));
  GC_register_finalizer(retval, finalize_program, 0, 0, 0);
  retval->vertex_shader = make_shader(GL_VERTEX_SHADER, vertex_shader_file_name);
  retval->fragment_shader = make_shader(GL_FRAGMENT_SHADER, fragment_shader_file_name);
  retval->program = glCreateProgram();
  retval->n_attributes = 0;
  retval->attribute_pointer = 0;
  if (retval->vertex_shader && retval->fragment_shader) {
    glAttachShader(retval->program, retval->vertex_shader->shader);
    glAttachShader(retval->program, retval->fragment_shader->shader);
    glLinkProgram(retval->program);
    if (!report_link_status(retval->program))
      retval = NULL;
  } else
    retval = NULL;
  return retval;
}

void test_add_vertex_array_object(CuTest *tc)
{
  object_t *object = make_object(make_rgb(0, 0, 0), 1);
  program_t *program = make_program("vertex-identity.glsl", "fragment-blue.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, make_surface(9, 3));
  object_t *retval = add_vertex_array_object(object, vertex_array_object);
  CuAssertIntEquals(tc, 1, object->n_vertex_array_objects);
  CuAssertPtrEquals(tc, vertex_array_object, object->vertex_array_object[0]);
  CuAssertPtrEquals(tc, object, retval);
}

void setup_vertex_attribute_pointer(vertex_array_object_t *vertex_array_object, const char *attribute, int size, int stride)
{
  glBindVertexArray(vertex_array_object->vertex_array_object);
  program_t *program = vertex_array_object->program;
  GLuint index = glGetAttribLocation(program->program, attribute);
  glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)program->attribute_pointer);
  glEnableVertexAttribArray(program->n_attributes);
  program->n_attributes += 1;
  program->attribute_pointer += sizeof(float) * size;
}

void test_shader_file_not_found(CuTest *tc)
{
  CuAssertPtrEquals(tc, NULL, make_shader(GL_VERTEX_SHADER, "no-such-file.glsl"));
}

void test_compile_shader(CuTest *tc)
{
  CuAssertTrue(tc, make_shader(GL_VERTEX_SHADER, "vertex-identity.glsl") != NULL);
}

void test_shader_syntax_error(CuTest *tc)
{
  freopen("/dev/null", "w", stderr);
  CuAssertPtrEquals(tc, NULL, make_shader(GL_VERTEX_SHADER, "invalid.glsl"));
  freopen("/dev/stderr", "w", stderr);
}

void test_no_vertex_shader(CuTest *tc)
{
  CuAssertPtrEquals(tc, NULL, make_program("no-such-file.glsl", "fragment-blue.glsl"));
}

void test_no_fragment_shader(CuTest *tc)
{
  CuAssertPtrEquals(tc, NULL, make_program("vertex-identity.glsl", "no-such-file.glsl"));
}

void test_compile_program(CuTest *tc)
{
  CuAssertTrue(tc, make_program("vertex-identity.glsl", "fragment-blue.glsl") != NULL);
}

void test_no_attribute_pointers(CuTest *tc)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  CuAssertIntEquals(tc, 0, program->n_attributes);
  CuAssertIntEquals(tc, 0, program->attribute_pointer);
}

void test_add_attribute_pointer(CuTest *tc)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  surface_t *surface = make_surface(9, 3);
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 5);
  CuAssertIntEquals(tc, 1, program->n_attributes);
  CuAssertIntEquals(tc, 3 * sizeof(float), program->attribute_pointer);
}

void test_add_two_attribute_pointers(CuTest *tc)
{
  program_t *program = make_program("vertex-texcoord.glsl", "fragment-blue.glsl");
  surface_t *surface = make_surface(9, 3);
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 5);
  setup_vertex_attribute_pointer(vertex_array_object, "texcoord", 2, 5);
  CuAssertIntEquals(tc, 2, program->n_attributes);
  CuAssertIntEquals(tc, 5 * sizeof(float), program->attribute_pointer);
}

void test_draw_triangle(CuTest *tc)
{
  surface_t *surface = make_surface(9, 3);
  add_vertex(surface, make_vertex( 0.5f,  0.5f, 0.0f));
  add_vertex(surface, make_vertex(-0.5f,  0.5f, 0.0f));
  add_vertex(surface, make_vertex(-0.5f, -0.5f, 0.0f));
  build_facet(surface, 0, 0);
  build_facet(surface, 1, 1);
  build_facet(surface, 2, 2);
  program_t *program = make_program("vertex-identity.glsl", "fragment-blue.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 3);
  object_t *object = make_object(make_rgb(0, 1, 0), 1);
  add_vertex_array_object(object, vertex_array_object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  render(object);
  glFlush();
  unsigned char *data = read_pixels();
  write_ppm("draw_triangle.ppm", width, height, data);
  CuAssertIntEquals(tc,   0, data[0]);
  CuAssertIntEquals(tc, 255, data[1]);
  CuAssertIntEquals(tc,   0, data[2]);
  CuAssertIntEquals(tc,   0, data[(12 * 32 + 14 ) * 4 + 0]);
  CuAssertIntEquals(tc,   0, data[(12 * 32 + 14 ) * 4 + 1]);
  CuAssertIntEquals(tc, 255, data[(12 * 32 + 14 ) * 4 + 2]);
}

void test_draw_two_surfaces(CuTest *tc)
{
  float coord[] = {0.5f, -0.5f};
  const char *fragment_shader_file_name[] = {"fragment-blue.glsl", "fragment-red.glsl"};
  object_t *object = make_object(make_rgb(0, 1, 0), 2);
  int i;
  for (i=0;i<2; i++) {
    surface_t *surface = make_surface(9, 3);
    float c = coord[i];
    add_vertex(surface, make_vertex(    c,     c, 0.0f));
    add_vertex(surface, make_vertex(-0.5f,  0.5f, 0.0f));
    add_vertex(surface, make_vertex( 0.5f, -0.5f, 0.0f));
    build_facet(surface, 0, 0);
    build_facet(surface, 1, 1);
    build_facet(surface, 2, 2);
    program_t *program = make_program("vertex-identity.glsl", fragment_shader_file_name[i]);
    vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
    setup_vertex_attribute_pointer(vertex_array_object, "point", 3, 3);
    add_vertex_array_object(object, vertex_array_object);
  };
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  render(object);
  glFlush();
  unsigned char *data = read_pixels();
  write_ppm("draw_surfaces.ppm", width, height, data);
  CuAssertIntEquals(tc,   0, data[0]);
  CuAssertIntEquals(tc, 255, data[1]);
  CuAssertIntEquals(tc,   0, data[2]);
  CuAssertIntEquals(tc, 255, data[( 8 * 32 + 14 ) * 4 + 0]);
  CuAssertIntEquals(tc,   0, data[( 8 * 32 + 14 ) * 4 + 1]);
  CuAssertIntEquals(tc,   0, data[( 8 * 32 + 14 ) * 4 + 2]);
  CuAssertIntEquals(tc,   0, data[(12 * 32 + 18 ) * 4 + 0]);
  CuAssertIntEquals(tc,   0, data[(12 * 32 + 18 ) * 4 + 1]);
  CuAssertIntEquals(tc, 255, data[(12 * 32 + 18 ) * 4 + 2]);
}

void test_use_normal(CuTest *tc)
{
  surface_t *surface = make_surface(9, 3);
  add_vertex(surface, make_vertex( 0.5f,  0.5f, 0.0f));
  add_normal(surface, make_normal( 0.0f,  0.0f, 1.0f));
  add_vertex(surface, make_vertex(-0.5f,  0.5f, 0.0f));
  add_normal(surface, make_normal( 0.0f,  1.0f, 0.0f));
  add_vertex(surface, make_vertex(-0.5f, -0.5f, 0.0f));
  add_normal(surface, make_normal( 1.0f,  0.0f, 0.0f));
  build_facet(surface, 0, 0);
  build_facet(surface, 1, 1);
  build_facet(surface, 2, 2);
  program_t *program = make_program("vertex-normal-identity.glsl", "fragment-normal.glsl");
  vertex_array_object_t *vertex_array_object = make_vertex_array_object(program, surface);
  setup_vertex_attribute_pointer(vertex_array_object, "point" , 3, 6);
  setup_vertex_attribute_pointer(vertex_array_object, "vector", 3, 6);
  object_t *object = make_object(make_rgb(0, 0, 0), 1);
  add_vertex_array_object(object, vertex_array_object);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  render(object);
  glFlush();
  unsigned char *data = read_pixels();
  write_ppm("use_normal.ppm", width, height, data);
  CuAssertTrue(tc, data[( 5 * 32 + 8 ) * 4 + 0] >= 192);
  CuAssertTrue(tc, data[(14 * 32 + 8 ) * 4 + 0] <   64);
  CuAssertTrue(tc, data[(14 * 32 + 8 ) * 4 + 1] >= 192);
}

void read_image(const char *file_name, int *width, int *height)
{
  ExceptionInfo *exception_info = AcquireExceptionInfo();
  ImageInfo *image_info = CloneImageInfo((ImageInfo *)NULL);
  CopyMagickString(image_info->filename, file_name, MaxTextExtent);
  Image *images = ReadImage(image_info, exception_info);
  Image *image = RemoveFirstImageFromList(&images);
  *width = image->columns;
  *height = image->rows;
  DestroyImage(image);
  DestroyImageInfo(image_info);
  DestroyExceptionInfo(exception_info);
}

void test_image_size(CuTest *tc)
{
  int width = 0;
  int height = 0;
  read_image("colors.png", &width, &height);
  CuAssertIntEquals(tc, 64, width);
  CuAssertIntEquals(tc, 64, height);
}

CuSuite *opengl_suite(void)
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_rgb);
  SUITE_ADD_TEST(suite, test_vertex);
  SUITE_ADD_TEST(suite, test_normal);
  SUITE_ADD_TEST(suite, test_empty_surface);
  SUITE_ADD_TEST(suite, test_add_one_vertex);
  SUITE_ADD_TEST(suite, test_add_two_vertices);
  SUITE_ADD_TEST(suite, test_add_normal);
  SUITE_ADD_TEST(suite, test_size_of_array);
  SUITE_ADD_TEST(suite, test_clear_buffer);
  SUITE_ADD_TEST(suite, test_empty_object);
  SUITE_ADD_TEST(suite, test_add_vertex_array_object);
  SUITE_ADD_TEST(suite, test_no_indices);
  SUITE_ADD_TEST(suite, test_size_of_indices);
  SUITE_ADD_TEST(suite, test_add_triangle);
  SUITE_ADD_TEST(suite, test_add_square);
  SUITE_ADD_TEST(suite, test_add_pentagon);
  SUITE_ADD_TEST(suite, test_shader_file_not_found);
  SUITE_ADD_TEST(suite, test_compile_shader);
  SUITE_ADD_TEST(suite, test_shader_syntax_error);
  SUITE_ADD_TEST(suite, test_no_vertex_shader);
  SUITE_ADD_TEST(suite, test_no_fragment_shader);
  SUITE_ADD_TEST(suite, test_compile_program);
  SUITE_ADD_TEST(suite, test_no_attribute_pointers);
  SUITE_ADD_TEST(suite, test_add_attribute_pointer);
  SUITE_ADD_TEST(suite, test_add_two_attribute_pointers);
  SUITE_ADD_TEST(suite, test_draw_triangle);
  SUITE_ADD_TEST(suite, test_draw_two_surfaces);
  SUITE_ADD_TEST(suite, test_use_normal);
  SUITE_ADD_TEST(suite, test_image_size);
  return suite;
}

int main(int argc, char *argv[])
{
  GC_INIT();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(width, height);
  glutCreateWindow("test");
  glewExperimental = 1;
  glewInit();
	CuString *output = CuStringNew();
  CuSuite *suite = opengl_suite();
  CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
  glFlush();
  int retval = suite->failCount > 0 ? 1 : 0;
  GC_gcollect();
  return retval;
}
