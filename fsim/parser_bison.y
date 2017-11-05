%{
#include <stdio.h>
#include "object.h"
#include "surface.h"
#include "list.h"
#include "hash.h"


#define YYERROR_VERBOSE 1

extern object_t *parse_result;
extern hash_t *parse_materials;
extern material_t *parse_material;
extern list_t *parse_vertex;
extern list_t *parse_uv;
extern list_t *parse_normal;
extern hash_t *parse_hash;

extern int yylex(void);

void yyerror(const char *message)
{
  fprintf(stderr, "%s\n", message);
}

static surface_t *last_surface(void)
{
  list_t *surface = parse_result->surface;
  return get_pointer(surface)[surface->size - 1];
}

static void copy_vertex_data(int index, int stride, list_t *source)
{
  surface_t *surface = last_surface();
  int i;
  for (i=index * stride; i<index * stride + stride; i++)
    append_glfloat(surface->array, get_glfloat(source)[i]);
}

static int index_vertex(int stride, int vertex_index, int uv_index, int normal_index)
{
  if (vertex_index < 0) vertex_index += 1 + parse_vertex->size / 3;
  if (uv_index     < 0) uv_index     += 1 + parse_uv->size     / 2;
  if (normal_index < 0) normal_index += 1 + parse_normal->size / 3;
  surface_t *surface = last_surface();
  surface->stride = stride;
  int n_indices = surface->array->size / stride;
  int result = hash_find_index(parse_hash, vertex_index, uv_index, normal_index, n_indices);
  if (result == n_indices) {
    copy_vertex_data(vertex_index - 1, 3, parse_vertex);
    if (uv_index) copy_vertex_data(uv_index - 1, 2, parse_uv);
    if (normal_index) copy_vertex_data(normal_index - 1, 3, parse_normal);
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
%token OBJECT MATERIAL KA MAPKD USE VERTEX UV NORMAL SURFACE FACET SLASH
%token <text> NAME
%token <number> NUMBER
%token <index> INDEX

%%

start: object materials vectors surfaces
     | /* NULL */
     ;

object: OBJECT NAME { parse_result = make_object($2); }

materials: material
         | /* NULL */
         ;

material: MATERIAL NAME {
            parse_material = make_material();
            hash_find_material(parse_materials, $2, parse_material);
          } properties

properties: property properties
          | /* NULL */
          ;

property: KA NUMBER NUMBER NUMBER {
            parse_material->ambient[0] = $2;
            parse_material->ambient[1] = $3;
            parse_material->ambient[2] = $4;
          }
        | MAPKD NAME {
            parse_material->texture = read_image($2);
          }

vectors: vector vectors
       | /* NULL */
       ;

vector: vertex
      | texture_coordinate
      | normal

vertex: VERTEX NUMBER NUMBER NUMBER {
          append_glfloat(parse_vertex, $2);
          append_glfloat(parse_vertex, $3);
          append_glfloat(parse_vertex, $4);
        }

texture_coordinate: UV NUMBER NUMBER {
                      append_glfloat(parse_uv, $2);
                      append_glfloat(parse_uv, $3);
                    }

normal: NORMAL NUMBER NUMBER NUMBER {
          append_glfloat(parse_normal, $2);
          append_glfloat(parse_normal, $3);
          append_glfloat(parse_normal, $4);
        }

surfaces: surface surfaces
        | /* NULL */
        ;

surface: SURFACE {
           add_surface(parse_result, make_surface(0));
           parse_hash = make_hash();
         } use_material facets

use_material: USE NAME {
              last_surface()->material = hash_find_material(parse_materials, $2, NULL);
            }
            | /* NULL */
            ;

facets: facet facets
      | /* NULL */
      ;

facet: FACET indices more_indices

indices: index index index {
           add_triangle(last_surface(), $1, $2, $3);
         }

more_indices: index {
                extend_triangle(last_surface(), $1);
              } more_indices
            | /* NULL */
            ;

index: INDEX {
         $$ = index_vertex(3, $1, 0, 0);
       }
       | INDEX SLASH INDEX {
         $$ = index_vertex(5, $1, $3, 0);
       }
       | INDEX SLASH SLASH INDEX {
         $$ = index_vertex(6, $1, 0, $4);
       }
       | INDEX SLASH INDEX SLASH INDEX {
         $$ = index_vertex(8, $1, $3, $5);
       }
