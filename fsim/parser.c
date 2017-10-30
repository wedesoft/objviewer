#include "parser.h"
#include "hash.h"


// https://stackoverflow.com/questions/780676/string-input-to-flex-lexer
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyparse(void);
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

object_t *parse_result = NULL;
list_t *parse_array = NULL;
list_t *parse_surface = NULL;
hash_t *parse_hash =  NULL;


object_t *parse_string_core(const char *text)
{
  parse_result = NULL;
  parse_array = make_list();
  parse_surface = make_list();
  YY_BUFFER_STATE buffer = yy_scan_string(text);
  if (yyparse())
    parse_result = NULL;
  yy_delete_buffer(buffer);
  return parse_result;
}

object_t *parse_string(const char *text)
{
  object_t *result = parse_string_core(text);
  parse_result = NULL;
  parse_array = NULL;
  parse_surface = NULL;
  parse_hash = NULL;
  return result;
}
