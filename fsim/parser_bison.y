%{
#include <assert.h>
#include <stdio.h>
#include "object.h"
#include "group.h"
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
extern int yylineno;

extern int yylex(void);

void yyerror(const char *message)
{
  fprintf(stderr, "Parsing line %d: %s\n", yylineno, message);
}

static group_t *last_group(void)
{
  list_t *group = parse_result->group;
  return get_pointer(group)[group->size - 1];
}

static void copy_vertex_data(int index, int stride, list_t *source)
{
  group_t *group = last_group();
  int i;
  assert(index >= 0);
  assert(index * stride < source->size);
  for (i=index * stride; i<index * stride + stride; i++)
    append_glfloat(group->array, get_glfloat(source)[i]);
}

static int index_vertex(int stride, int vertex_index, int uv_index, int normal_index)
{
  if (vertex_index < 0) vertex_index += 1 + parse_vertex->size / 3;
  if (uv_index     < 0) uv_index     += 1 + parse_uv->size     / 2;
  if (normal_index < 0) normal_index += 1 + parse_normal->size / 3;
  group_t *group = last_group();
  group->stride = stride;
  int n_indices = group->array->size / stride;
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
  material_t *material;
}

%type<index> index
%type<material> use_material
%token OBJECT MATERIAL KA KD KS NS NI D MAPKD USE VERTEX UV NORMAL GROUP FACET SLASH
%token <text> NAME
%token <number> NUMBER
%token <index> INDEX

%%

start: materials object primitives
     | /* NULL */
     ;

object: OBJECT NAME { parse_result = make_object($2); }

primitives: primitives primitive
          | /* NULL */
          ;

materials: materials material
         | /* NULL */
         ;

material: MATERIAL NAME {
            parse_material = make_material();
            hash_find_material(parse_materials, $2, parse_material);
          } properties

properties: properties property
          | /* NULL */
          ;

property: KA NUMBER NUMBER NUMBER { set_ambient(parse_material, $2, $3, $4); }
        | KD NUMBER NUMBER NUMBER { set_diffuse(parse_material, $2, $3, $4); }
        | KS NUMBER NUMBER NUMBER { set_specular(parse_material, $2, $3, $4); }
        | NS NUMBER               { set_specular_exponent(parse_material, $2); }
        | NI NUMBER               { set_optical_density(parse_material, $2); }
        | D NUMBER                { set_disolve(parse_material, $2); }
        | MAPKD NAME              { set_texture(parse_material, read_image($2)); }

primitive: group
         | vertex
         | texture_coordinate
         | normal
         | facet
         ;

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

group: GROUP use_material {
         add_group(parse_result, make_group(0));
         use_material(last_group(), $2);
         parse_hash = make_hash();
       }
     | use_material GROUP {
         add_group(parse_result, make_group(0));
         use_material(last_group(), $1);
         parse_hash = make_hash();
       }
     | GROUP {
         add_group(parse_result, make_group(0));
         parse_hash = make_hash();
       }

use_material: USE NAME { $$ = hash_find_material(parse_materials, $2, NULL); }

facet: FACET indices more_indices

indices: index index index { add_triangle(last_group(), $1, $2, $3); }

more_indices: index { extend_triangle(last_group(), $1); } more_indices
            | /* NULL */
            ;

index: INDEX                           { $$ = index_vertex(3, $1,  0,  0); }
       | INDEX SLASH INDEX             { $$ = index_vertex(5, $1, $3,  0); }
       | INDEX SLASH SLASH INDEX       { $$ = index_vertex(6, $1,  0, $4); }
       | INDEX SLASH INDEX SLASH INDEX { $$ = index_vertex(8, $1, $3, $5); }
