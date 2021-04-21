/* file parseur.y */
/* compilation: bison -d parseur.y */
/* result: parseur.tab.c = C code for syntaxic analyser */
/* result: parseur.tab.h = def. of lexical units aka lexems */

%{
	#include <stdio.h>       /* printf */
%}


%{
	int yylex(void);/* -Wall : avoid implicit call */
	int yyerror(const char*);/* same for bison */
%}

%token <ival> NOMBRE 

%type <ival> expression

%left '+' '-'
%left '*' '/'
%nonassoc MOINSU

%union {
	double dval;
	int ival; 
};

%%

resultat: expression  { printf("Resultat= %d\n",$1); } ;

expression:
	 expression'+'expression {$$=$1+$3; }
	|expression'-'expression {$$=$1-$3; }
	|expression'*'expression {$$=$1*$3; }
	|expression'/'expression {$$=$1/$3; }
	|'('expression')' {$$= $2; }
	|'-'expression %prec MOINSU {$$= -$2; }
	| NOMBRE {$$=$1; }
	;
%%

#include <stdio.h>        /* printf */
int yyerror(const char *msg){ printf("Parsing:: syntax error\n"); return 1;}int yywrap(void){ return 1; }/* stop reading flux yyin */
