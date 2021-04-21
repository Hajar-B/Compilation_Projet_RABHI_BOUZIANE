/* file main.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */

#include <stdio.h>        /* printf */
#include <stdlib.h>        /* exit */
#include "parseur.tab.h"

extern FILE* yyin;
extern int yy_scan_string(const char *);

int main(int argc, char *argv[]){
  FILE* tmp;
  //tmp = fopen(argv[1],"r+");
  if( argc == 2){
	  if((tmp = fopen(argv[1],"r")) != NULL){
		  yyin = tmp;
		 
	  }
	  yyparse();
	  printf("Parsing:: syntax OK\n"); /* reached if parsing folllows the grammar */
	  fclose(tmp);
   }
   else{
   	printf("Entrez votre expression : ");
   	char buff[50];
   	scanf("%s", buff);
   	yy_scan_string(buff);
   	
   	if (yyparse()==0) { /* yyparse calls yylex */
		  printf("\nParsing:: syntax OK\n"); /* reached if parsing folllows the grammar */
		  
	}
   }
  exit(EXIT_SUCCESS);
}
