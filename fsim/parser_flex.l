%{
#include "object.h"
#include "parser_bison.h"
%}

%option noyywrap

%x name nmb idx mtllib

%%

"o "                                       { BEGIN(name); return OBJECT; }

"mtllib "                                  BEGIN(mtllib);

"newmtl "                                  { BEGIN(name); return MATERIAL; }

v                                          { BEGIN(nmb); return VERTEX; }

vt                                         { BEGIN(nmb); return UV; }

vn                                         { BEGIN(nmb); return NORMAL; }

"s off"                                    return SURFACE;

f                                          { BEGIN(idx); return FACET; }

<name>.*                                   { yylval.text = yytext; return NAME; }
<name>\n                                   BEGIN(INITIAL);

<nmb>[+-]?[0-9]*(\.[0-9]*)?(e[+-]?[0-9]+)? { yylval.number = atof(yytext); return NUMBER; }
<nmb>" "                                   ;
<nmb>\n                                    BEGIN(INITIAL);

<idx>[0-9]*                                { yylval.index = atoi(yytext); return INDEX; }
<idx>"/"                                   return SLASH;
<idx>" "                                   ;
<idx>\n                                    BEGIN(INITIAL);

<mtllib>.*                                 {
                                             yyin = fopen(yytext, "r");
                                             if (yyin)
                                               yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
                                             BEGIN(INITIAL);
                                           }

[\n ]                                      ;

<<EOF>>                                    {
                                             if (yy_buffer_stack_top > 0)
                                               fclose(yyin);
                                             yypop_buffer_state();
                                             if (!YY_CURRENT_BUFFER)
                                               yyterminate();
                                           }

.                                          return *yytext;

%%
