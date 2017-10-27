%{
#include "object.h"
#include "parser_bison.h"
%}

%option noyywrap

%x name

%%

"o "     { BEGIN(name); return OBJECT; }

<name>.* { yylval.text = yytext; return NAME; }
<name>\n BEGIN(INITIAL);

%%
