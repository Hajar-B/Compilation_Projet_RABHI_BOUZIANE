/* file parseur.y */
/* compilation: bison -d parseur.y */
/* result: parseur.tab.c = C code for syntaxic analyser */
/* result: parseur.tab.h = def. of lexical units aka lexems */

%{
	int yylex(void);/* -Wall : avoid implicit call */
	int yyerror(const char*);/* same for bison */
%}


%token NOMBRE FLOAT BOOLEAN 
%token PT_VIRG EQUALS NOTEQL GREQ LOEQ
%token IDENT

%left '='
%left EQUALS NOTEQL LOEQ '<' GREQ '>' 
%left '+' '-'
%left '*' '/'
%left '!'
%nonassoc MOINSU

%start resultat

%%

resultat : programme;

programme: commande PT_VIRG
	| commande PT_VIRG programme 
	;

commande: expression 
	| IDENT '=' expression
	;

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
	| IDENT
	;
%%

#include <stdio.h>        /* printf */
int yyerror(const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; }/* stop reading flux yyin */
