#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "parser.h"
#include "hash.h"


// https://stackoverflow.com/questions/780676/string-input-to-flex-lexer
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern void yyrestart (FILE *input_file);
extern int yyparse(void);
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

object_t *parse_result = NULL;
hash_t *parse_materials = NULL;
material_t *parse_material = NULL;
material_t *parse_use_material = NULL;
list_t *parse_vertex = NULL;
list_t *parse_uv = NULL;
list_t *parse_normal = NULL;
hash_t *parse_hash =  NULL;


static void parser_init(void)
{
  parse_result = NULL;
  parse_material = NULL;
  parse_materials = make_hash();
  parse_use_material = NULL;// TODO: test
  parse_vertex = make_list();
  parse_uv = make_list();
  parse_normal = make_list();
  parse_hash = NULL;
}

static void parser_cleanup(void)
{
  parse_result = NULL;
  parse_material = NULL;// TODO: test
  parse_use_material = NULL;// TODO: test
  parse_vertex = NULL;
  parse_uv = NULL;
  parse_normal = NULL;
  parse_hash = NULL;
}

object_t *parse_string_core(const char *text)
{
  parser_init();
  YY_BUFFER_STATE buffer = yy_scan_string(text);
  if (yyparse())
    parse_result = NULL;
  return parse_result;
}

object_t *parse_file_core(const char *file_name)
{
  parser_init();
  FILE *f = fopen(file_name, "r");
  if (!f) {
    fprintf(stderr, "Error opening file %s: %s\n", file_name, strerror(errno));
    parse_result = NULL;
  } else {
    yyrestart(f);
    if (yyparse())
      parse_result = NULL;
    fclose(f);
  };
  return parse_result;
}

object_t *parse_string(const char *text)
{
  object_t *result = parse_string_core(text);
  parser_cleanup();
  return result;
}

object_t *parse_file(const char *file_name)
{
  object_t *result = parse_file_core(file_name);
  parser_cleanup();
  return result;
}
