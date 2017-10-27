#include "parser.h"

// https://stackoverflow.com/questions/780676/string-input-to-flex-lexer
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyparse(void);
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

object_t *parse_result;


object_t *parse_string(const char *text)
{
  parse_result = NULL;
  YY_BUFFER_STATE buffer = yy_scan_string(text);
  yyparse();
  yy_delete_buffer(buffer);
  return parse_result;
}
