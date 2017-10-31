%{
#include <stdio.h>
#include "object.h"
#include "surface.h"
#include "list.h"
#include "hash.h"


extern object_t *parse_result;
extern list_t *parse_vertex;
extern list_t *parse_texture_coordinate;
extern hash_t *parse_hash;
extern list_t *parse_surface;

extern int yylex(void);

void yyerror(const char *message)
{
  fprintf(stderr, "%s\n", message);
}

static surface_t *last_surface(void)
{
  return get_pointer(parse_surface)[parse_surface->size - 1];
}

static void copy_vertex(int index)
{
  surface_t *surface = last_surface();
  int i;
  for (i=index * 3; i<index * 3 + 3; i++)
    append_glfloat(surface->array, get_glfloat(parse_vertex)[i]);
}

static int vertex_index(int wavefront_index)
{
  int n_indices = last_surface()->array->size / 3;
  int result = hash_find(parse_hash, wavefront_index, n_indices);
  if (result == n_indices)
    copy_vertex(wavefront_index - 1);
  return result;
}

%}

%union {
  char *text;
  float number;
  int index;
}

%token OBJECT VERTEX SURFACE FACET
%token <text> NAME
%token <number> NUMBER
%token <index> INDEX

%%

start: OBJECT NAME { parse_result = make_object($2); } vertices surfaces
     | /* NULL */
     ;

vertices: VERTEX NUMBER NUMBER NUMBER {
            append_glfloat(parse_vertex, $2);
            append_glfloat(parse_vertex, $3);
            append_glfloat(parse_vertex, $4);
          } vertices
        | /* NULL */
        ;

surfaces: SURFACE {
            append_pointer(parse_surface, make_surface());
            parse_hash = make_hash();
          } facets surfaces
        | /* NULL */
        ;

facets: FACET indices facets
      | /* NULL */
      ;

indices: INDEX INDEX INDEX {
           int index1 = vertex_index($1);
           int index2 = vertex_index($2);
           int index3 = vertex_index($3);
           add_triangle(last_surface(), index1, index2, index3);
         } more_indices
       ;

more_indices: INDEX {
                int index = vertex_index($1);
                extend_triangle(last_surface(), index);
              } more_indices
            | /* NULL */
            ;
