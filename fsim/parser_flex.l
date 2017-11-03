%{
#include "object.h"
#include "parser_bison.h"
%}

%option noyywrap

%x name nmb idx

%%

"o "                                       { BEGIN(name); return OBJECT; }

"mtllib "                                  { BEGIN(name); return MTLLIB; }

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

[\n ]                                      ;

.                                          return *yytext;

%%
