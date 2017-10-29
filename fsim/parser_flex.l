%{
#include "object.h"
#include "parser_bison.h"
%}

%option noyywrap

%x name nmb idx

%%

"o "                   { BEGIN(name); return OBJECT; }

"v "                   { BEGIN(nmb); return VERTEX; }

"s off"                return SURFACE;

"f "                   { BEGIN(idx); return FACET; }

<name>.*               { yylval.text = yytext; return NAME; }
<name>\n               BEGIN(INITIAL);

<nmb>[+-]?[0-9]*(\.[0-9]*)? { yylval.number = atof(yytext); return NUMBER; }
<nmb>" "               ;
<nmb>\n                BEGIN(INITIAL);

<idx>[0-9]*            return INDEX;
<idx>" "               ;
<idx>\n                BEGIN(INITIAL);

[\n ]                  ;

.                      return *yytext;

%%
