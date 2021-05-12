/* file parseur.y */
/* compilation: bison -d parseur.y */
/* result: parseur.tab.c = C code for syntaxic analyser */
/* result: parseur.tab.h = def. of lexical units aka lexems */

/* comlements: https://www.gnu.org/software/bison/manual/html_node/Parser-Function.html */
/* about implicit call: https://stackoverflow.com/questions/20106574/simple-yacc-grammars-give-an-error */

%{
 #include <stdio.h>	/* printf REMOVE AFTER TEST */
 #include "AST.h"
 
 int yylex(void);	/* flex with -Wall (implicite call) */
 int yyerror(struct _tree**, const char*); /* same for bison */
%}


%parse-param {struct _tree* *pT} // yyparse(&t) call => *pT = *(&t) = t 

%union {
  struct _tree* exp;
  char* numf;
  char* boo;
  char* ide;
} ;

%type  <exp> expression
%type  <exp> programme_ast
%type  <exp> commande_ast
%token <numf>NUMBER <boo>BOOLEAN <boo>NAN <ide>IDENT
%token PT_VIRG EQUALS NOTEQL GREQ LOEQ INCRE
%token IF ELSE

%left '='
%left EQUALS NOTEQL LOEQ '<' GREQ '>' 
%left '+' '-'
%left '*' '/'
%left '!'
%left INCRE
%nonassoc MOINSU

%start resultat

%%


resultat : programme_ast { *pT = $1; };

programme_ast: commande_ast	      { $$ = $1; }
	| commande_ast programme_ast { $$ = newBinaryAST("prog",$1,$2);}
	;


commande_ast: expression PT_VIRG	{ $$ = $1; }
	| IDENT '=' expression PT_VIRG { $$ = newBinaryASTide("=",$1,$3); } 
	| IF '('expression')' commande_ast ELSE commande_ast {$$ = newBinaryAST("IfElse",newBinaryAST("If",$3,$5),newUnaryAST("Else",$7));}
	;	
	
	
expression:
    expression '+' expression	{ $$ = newBinaryAST("+",$1,$3); }
  | expression '-' expression	{ $$ = newBinaryAST("-",$1,$3); }
  | expression '*' expression	{ $$ = newBinaryAST("*",$1,$3); }
  | expression '/' expression	{ $$ = newBinaryAST("/",$1,$3); }
  | '(' expression ')'		 { $$ = $2; }
  | '-' expression %prec MOINSU { $$ = newUnaryAST("-",$2); }
  |expression EQUALS expression { $$ = newBinaryAST("==",$1,$3); }
  |expression NOTEQL expression { $$ = newBinaryAST("!=",$1,$3); }
  |expression GREQ expression	 { $$ = newBinaryAST(">=",$1,$3); }
  |expression '>' expression	 { $$ = newBinaryAST(">",$1,$3); }
  |expression LOEQ expression   { $$ = newBinaryAST("<=",$1,$3); }
  |expression '<' expression    { $$ = newBinaryAST("<",$1,$3); }
  |'!'expression		 { $$ = newUnaryAST("!",$2); } 
  | NUMBER			 { $$ = newLeafAST($1); } 
  | BOOLEAN			 { $$ = newLeafASTb($1); } 
  | IDENT			 { $$ = newLeafASTide($1); }
  | IDENT INCRE		 { $$ = newUnaryASTide($1,"++");}
  | NAN			 { $$ = newLeafASTb($1); }
  ;

%%

#include <stdio.h>	/* printf */
int yyerror(struct _tree **pT, const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; } /* stop reading flux yyin */
