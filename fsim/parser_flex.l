%{
#include "object.h"
#include "parser_bison.h"
%}

%option noyywrap

%x name

%%

"o "              { BEGIN(name); return OBJECT; }

"v "              return VERTEX;

"s off"           return SURFACE;

<name>.*          { yylval.text = yytext; return NAME; }
<name>\n          BEGIN(INITIAL);

[0-9]*(\.[0-9]*)? { yylval.number = atof(yytext); return NUMBER; }
[\n ]             ;

.                 return *yytext;

%%
