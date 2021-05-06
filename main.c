/* file main.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */

#include <stdio.h>        /* printf */
#include <stdlib.h>        /* exit */
#include "parseur.tab.h"
#include "AST.c"	/* AST fonctions */

extern FILE* yyin;
extern int yy_scan_string(const char *);

int main(int argc, char *argv[]){
  FILE* tmp;
  AST t; 				/* &t allows to modifie the tree */
  //tmp = fopen(argv[1],"r+");
  if( argc == 2){
	  if((tmp = fopen(argv[1],"r")) != NULL){
		  yyin = tmp;
		 
	  }
	  if ((yyparse(&t)==0)) { 		/* yyparse calls yylex */
	    printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
	    
	    /* print the obtained tree */
	    if (t->left!=NULL) printf("Root symbol:: %c\n", t->car);	/* check if car at root */
	    printAST(t); printf("\n");
	    		
    	    freeAST(t);
    	  }
	  fclose(tmp);
   }
   else{
   	printf("Entrez votre expression : ");
   	char buff[50];
   	scanf("%s", buff);
   	yy_scan_string(buff);
   	
   	if ((yyparse(&t)==0)) { 		/* yyparse calls yylex */
	    printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
	    
	    /* print the obtained tree */
	    if (t->left!=NULL) printf("Root symbol:: %c\n", t->car);	/* check if car at root */
	    printAST(t); printf("\n");
	    		
	    freeAST(t);
	}
   }
   
  exit(EXIT_SUCCESS);
}

