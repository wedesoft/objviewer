%{
#include <stdio.h>
#include "object.h"
#include "surface.h"
#include "list.h"


extern object_t *parse_result;
extern list_t *parse_array;
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
            append_glfloat(parse_array, $2);
            append_glfloat(parse_array, $3);
            append_glfloat(parse_array, $4);
          } vertices
        | /* NULL */
        ;

surfaces: SURFACE {
            append_pointer(parse_surface, make_surface());
          } facets surfaces
          | /* NULL */
          ;

facets: FACET indices
      | /* NULL */
      ;

indices: INDEX INDEX INDEX {
         add_polygon(last_surface(), 3, $1, $2, $3);
       }
       ;
