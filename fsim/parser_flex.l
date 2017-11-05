%{
#include "object.h"
#include "parser_bison.h"
%}

%option noyywrap

%x name idx mtllib

%%

#.*\n                                 ;

o[ ]+                                 { BEGIN(name); return OBJECT; }

mtllib[ ]+                            BEGIN(mtllib);

newmtl[ ]+                            { BEGIN(name); return MATERIAL; }

Ka                                    return KA;

usemtl[ ]+                            { BEGIN(name); return USE; }

v                                     return VERTEX;

vt                                    return UV;

vn                                    return NORMAL;

s.*                                   return SURFACE;

f                                     { BEGIN(idx); return FACET; }

<name>.*                              { yylval.text = yytext; return NAME; }
<name>\n                              BEGIN(INITIAL);

[+-]?[0-9]*(\.[0-9]*)?(e[+-]?[0-9]+)? { yylval.number = atof(yytext); return NUMBER; }

<idx>-?[0-9]*                           { yylval.index = atoi(yytext); return INDEX; }
<idx>"/"                              return SLASH;
<idx>" "                              ;
<idx>\n                               BEGIN(INITIAL);

<mtllib>.*                            {
                                        yyin = fopen(yytext, "r");
                                        if (yyin)
                                          yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
                                        BEGIN(INITIAL);
                                      }

[ \t\n]                               ;

<<EOF>>                               {
                                        if (yy_buffer_stack_top > 0)
                                          fclose(yyin);
                                        yypop_buffer_state();
                                        if (!YY_CURRENT_BUFFER)
                                          yyterminate();
                                      }

.                                     return *yytext;

%%
