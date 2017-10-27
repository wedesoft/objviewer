#include "parser.h"

object_t *parse_result;


void *parse_string(const char *text)
{
  parse_result = NULL;
  yyparse();
  return parse_result;
}
