/* file lexeur.l */
/* compilation: flex lexeur.l */
/* result: lex.yy.c = lexical analyser in C */
%{
	#include <stdio.h>       /* printf */
	#include "parseur.tab.h" /* token constants def. in parseur.y via #define */
%}

%%

0|[1-9][0-9]*  { printf("lex::NOMBRE %s\n",yytext); return NOMBRE; }
(0|[1-9][0-9]*)"."[0-9]* { printf("lex::FLOAT %s\n",yytext); return FLOAT; }
[a-z][0-9,A-Z,a-z,_]* { printf("lex::IDENT %s\n",yytext); return IDENT; }
"True"|"False" { printf("lex::BOOLEAN %s\n",yytext); return BOOLEAN; }
==		{ printf("lex::EQUALS %s\n",yytext); return EQUALS; }
!=		{ printf("lex::NOTEQL %s\n",yytext); return NOTEQL; }
>=		{ printf("lex::GREQ %s\n",yytext); return GREQ; }
"<="		{ printf("lex::LOEQ %s\n",yytext); return LOEQ; }
;		{ printf("lex::PT_VIRG %s\n",yytext); return PT_VIRG; }
[\t\n]         { ; }/* ignore space, tab, and line return */
.              { printf("lex::char %s\n",yytext); return yytext[0]; } /* other one-char = token, ex.'+'*/

%%
