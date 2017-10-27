%{
#include <stdio.h>
#include "object.h"


extern object_t *parse_result;

void yyerror(const char *message)
{
  fprintf(stderr, "%s\n", message);
}

%}

%union {
  object_t *object;
}

%type <object> start
%token OBJECT

%%

start: OBJECT { parse_result = make_object(); }
     | /* NULL */
     ;
