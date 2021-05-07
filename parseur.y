/* file parseur.y */
/* compilation: bison -d parseur.y */
/* result: parseur.tab.c = C code for syntaxic analyser */
/* result: parseur.tab.h = def. of lexical units aka lexems */

%{
	#include <stdio.h>

	int yylex(void);/* -Wall : avoid implicit call */
	int yyerror(const char*);/* same for bison */
%}


%token NOMBRE PT_VIRG FLOAT BOOLEAN EQUALS NOTEQL GREQ LOEQ

%left EQUALS NOTEQL LOEQ '<' GREQ '>' 
%left '+' '-'
%left '*' '/'
%left '!'
%nonassoc MOINSU


%%

/* faire des print pour vérifier les associativité et priorité */

resultat: expression PT_VIRG;

expression:
	 expression'+'expression {printf("AddiNb\n");}
	|expression'-'expression {printf("SubiNb\n");}
	|expression'*'expression {printf("MultNb\n");}
	|expression'/'expression {printf("DiviNb\n");}
	|'('expression')'
	|'-'expression %prec MOINSU   {printf("Moinsu\n");}
	|expression EQUALS expression {printf("Equals\n");}
	|expression NOTEQL expression {printf("NotEq\n");}
	|expression GREQ expression   {printf("GrEq\n");}
	|expression '>' expression    {printf("Gr\n");}
	|expression LOEQ expression   {printf("LoEq\n");}
	|expression '<' expression    {printf("Lo\n");}
	|'!'expression		       {printf("Not\n");}
	| NOMBRE 
	| FLOAT
	| BOOLEAN
	;
%%

//#include <stdio.h>        /* printf */
int yyerror(const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; }/* stop reading flux yyin */
