%{
#include <stdio.h>
#include "object.h"
#include "list.h"


extern object_t *parse_result;
extern list_t *parse_array;

extern int yylex(void);

void yyerror(const char *message)
{
  fprintf(stderr, "%s\n", message);
}

%}

%union {
  char *text;
  float number;
}

%token OBJECT VERTEX
%token <text> NAME
%token <number> NUMBER

%%

start: OBJECT NAME { parse_result = make_object($2); } vertices
     | /* NULL */
     ;

vertices: VERTEX NUMBER NUMBER NUMBER {
            append_glfloat(parse_array, $2);
            append_glfloat(parse_array, $3);
            append_glfloat(parse_array, $4);
          } vertices
        | /* NULL */
        ;
