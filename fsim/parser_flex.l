%{
#include "object.h"
#include "parser_bison.h"
%}

%option noyywrap
%option yylineno

%x name idx mtllib

%%

#.*\n                                 ;

o                                     { BEGIN(name); return OBJECT; }

mtllib                                BEGIN(mtllib);

newmtl                                { BEGIN(name); return MATERIAL; }

Ka                                    return KA;

Kd                                    return KD;

Ks                                    return KS;

Ns                                    return NS;

Ni                                    return NI;

d                                     return D;

map_Kd                                { BEGIN(name); return MAPKD; }

usemtl                                { BEGIN(name); return USE; }

v                                     return VERTEX;

vt                                    return UV;

vn                                    return NORMAL;

s.*                                   return SURFACE;

f                                     { BEGIN(idx); return FACET; }

<name>[^ \t\r\n][^\t\r\n]*            { yylval.text = yytext; return NAME; }

[+-]?[0-9]*(\.[0-9]*)?(e[+-]?[0-9]+)? { yylval.number = atof(yytext); return NUMBER; }

<idx>-?[0-9]*                         { yylval.index = atoi(yytext); return INDEX; }
<idx>"/"                              return SLASH;

<mtllib>[^ \t\r\n]*                   {
                                        yyin = fopen(yytext, "r");
                                        if (yyin)
                                          yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
                                        BEGIN(INITIAL);
                                      }

<INITIAL,name,idx,mtllib>[ \r\t]      ;
<INITIAL,name,idx,mtllib>\n           BEGIN(INITIAL);

<INITIAL,name,idx,mtllib><<EOF>>      {
                                        if (yy_buffer_stack_top > 0)
                                          fclose(yyin);
                                        yypop_buffer_state();
                                        if (!YY_CURRENT_BUFFER)
                                          yyterminate();
                                      }

<INITIAL,name,idx,mtllib>[^ \r\t\n]   {
                                        fprintf(stderr, "Line %d: unexpected character '%c'.\n", yylineno, *yytext);
                                        return *yytext;
                                      }

%%
