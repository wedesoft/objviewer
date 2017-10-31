#include "parser.h"
#include "hash.h"


// https://stackoverflow.com/questions/780676/string-input-to-flex-lexer
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyparse(void);
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

object_t *parse_result = NULL;
list_t *parse_vertex = NULL;
list_t *parse_uv = NULL;
hash_t *parse_hash =  NULL;
list_t *parse_surface = NULL;


object_t *parse_string_core(program_t *program, const char *text)
{
  parse_result = NULL;
  parse_vertex = make_list();
  parse_uv = make_list();
  parse_surface = make_list();
  YY_BUFFER_STATE buffer = yy_scan_string(text);
  if (yyparse())
    parse_result = NULL;
  if (parse_result) {
    int i;
    for (i=0; i<parse_surface->size; i++)
      add_vertex_array_object(parse_result, make_vertex_array_object(program, get_pointer(parse_surface)[i]));
  };
  yy_delete_buffer(buffer);
  return parse_result;
}

object_t *parse_string(program_t *program, const char *text)
{
  object_t *result = parse_string_core(program, text);
  parse_result = NULL;
  parse_vertex = NULL;
  parse_uv = NULL;
  parse_hash = NULL;
  parse_surface = NULL;
  return result;
}
