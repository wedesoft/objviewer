%{
#include <stdio.h>
#include "object.h"
#include "surface.h"
#include "list.h"
#include "hash.h"


extern object_t *parse_result;
extern list_t *parse_vertex;
extern list_t *parse_uv;
extern list_t *parse_normal;
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

static void copy_uv(int index)
{
  surface_t *surface = last_surface();
  int i;
  for (i=index * 2; i<index * 2 + 2; i++)
    append_glfloat(surface->array, get_glfloat(parse_uv)[i]);
}

static int index_vertex(int vertex_index)
{
  int n_indices = last_surface()->array->size / 3;
  int result = hash_find(parse_hash, vertex_index, n_indices);
  if (result == n_indices)
    copy_vertex(vertex_index - 1);
  return result;
}

static int index_vertex_uv(int vertex_index, int uv_index)
{
  int n_indices = last_surface()->array->size / 5;
  int result = hash_find_pair(parse_hash, vertex_index, uv_index, n_indices);
  if (result == n_indices) {
    copy_vertex(vertex_index - 1);
    copy_uv(uv_index - 1);
  };
  return result;
}

%}

%union {
  char *text;
  float number;
  int index;
}

%type<index> index
%token OBJECT VERTEX UV NORMAL SURFACE FACET SLASH
%token <text> NAME
%token <number> NUMBER
%token <index> INDEX

%%

start: OBJECT NAME { parse_result = make_object($2); } vertices texture_coordinates normals surfaces
     | /* NULL */
     ;

vertices: VERTEX NUMBER NUMBER NUMBER {
            append_glfloat(parse_vertex, $2);
            append_glfloat(parse_vertex, $3);
            append_glfloat(parse_vertex, $4);
          } vertices
        | /* NULL */
        ;

texture_coordinates: UV NUMBER NUMBER {
                     append_glfloat(parse_uv, $2);
                     append_glfloat(parse_uv, $3);
                   } texture_coordinates
                   | /* NULL */
                   ;

normals: NORMAL NUMBER NUMBER NUMBER {
           append_glfloat(parse_normal, $2);
           append_glfloat(parse_normal, $3);
           append_glfloat(parse_normal, $4);
         }
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

indices: index index index {
           add_triangle(last_surface(), $1, $2, $3);
         } more_indices
       ;

more_indices: index {
                extend_triangle(last_surface(), $1);
              } more_indices
            | /* NULL */
            ;

index: INDEX {
         $$ = index_vertex($1);
       }
       | INDEX SLASH INDEX {
         $$ = index_vertex_uv($1, $3);
       }
       ;
