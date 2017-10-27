%{
#include <stdio.h>
#include "object.h"


extern object_t *parse_result;

extern int yylex(void);

void yyerror(const char *message)
{
  fprintf(stderr, "%s\n", message);
}

%}

%union {
  char *text;
}

%token OBJECT
%token <text> NAME

%%

start: OBJECT NAME { parse_result = make_object($2); }
     | /* NULL */
     ;
