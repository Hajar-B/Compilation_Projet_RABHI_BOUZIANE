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
	 expression'+'expression 
	|expression'-'expression 
	|expression'*'expression 
	|expression'/'expression 
	|'('expression')'
	|'-'expression %prec MOINSU   
	|expression EQUALS expression 
	|expression NOTEQL expression 
	|expression GREQ expression   
	|expression '>' expression    
	|expression LOEQ expression   
	|expression '<' expression    
	|'!'expression			
	| NOMBRE 
	| FLOAT
	| BOOLEAN
	;
%%

//#include <stdio.h>        /* printf */
int yyerror(const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; }/* stop reading flux yyin */
