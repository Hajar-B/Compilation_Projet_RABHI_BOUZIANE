/* file lexeur.l */
/* compilation: flex lexeur.l */
/* result: lex.yy.c = lexical analyser in C */
%{
	#include <stdio.h>       /* printf */
	#include "parseur.tab.h" /* token constants def. in parseur.y via #define */
%}

%%

([a-z,A-Z,0-9,_]*|"0"?("."0*)?)"/"((".")?"0"|"0"("."0*)) { printf("lex::NAN %s\n",yytext); return NAN; }
(0|[1-9][0-9]*)(("."[0-9]*)?("e"-?[0-9]+)?)|("."[0-9]+)("e"-?[0-9]+)? { printf("lex::NUMBER %s\n",yytext); return NUMBER; }
[a-z][0-9,A-Z,a-z,_]* { printf("lex::IDENT %s\n",yytext); return IDENT; }
"True"|"False" { printf("lex::BOOLEAN %s\n",yytext); return BOOLEAN; }
"If" 		{ printf("lex::IF %s\n",yytext); return IF; }
"Else" 	{ printf("lex::ELSE %s\n",yytext); return ELSE; }
==		{ printf("lex::EQUALS %s\n",yytext); return EQUALS; }
!=		{ printf("lex::NOTEQL %s\n",yytext); return NOTEQL; }
>=		{ printf("lex::GREQ %s\n",yytext); return GREQ; }
"<="		{ printf("lex::LOEQ %s\n",yytext); return LOEQ; }
"++"		{ printf("lex::INCRE %s\n",yytext); return INCRE; }
;		{ printf("lex::PT_VIRG %s\n",yytext); return PT_VIRG; }
[\t\n ]         { ; }/* ignore space, tab, and line return */
"//"[^\n]* { ; }/* ignore space, tab, and line return */
"/*"([^*]|"*"+[^*/])*"*"+"/" { ; }/* ignore space, tab, and line return */
.              { printf("lex::char %s\n",yytext); return yytext[0]; } /* other one-char = token, ex.'+'*/

%%



