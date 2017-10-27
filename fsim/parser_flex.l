%{
#include "object.h"
#include "parser_bison.h"
%}

%option noyywrap

%x name vertex

%%

"o "                      { BEGIN(name); return OBJECT; }

"v "                      { BEGIN(vertex); return VERTEX; }

<name>.*                  { yylval.text = yytext; return NAME; }
<name>\n                  BEGIN(INITIAL);
<vertex>[0-9]*(\.[0-9]*)? { yylval.number = atof(yytext); return NUMBER; }
<vertex>[ ]               ;

.                         return *yytext;

%%
