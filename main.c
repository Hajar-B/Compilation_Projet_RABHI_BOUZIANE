/* file main.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */

#include <stdio.h>        /* printf */
#include <stdlib.h>        /* exit */
#include "parseur.tab.h"
#include "AST.c"	/* AST fonctions */
#include <string.h>

extern FILE* yyin;
extern int yy_scan_string(const char *);

int main(int argc, char *argv[]){
  FILE* tmp;
  AST t; 				/* &t allows to modifie the tree */
  
  // Si l'on a un fichier en argument
  if( argc == 2){
	  if((tmp = fopen(argv[1],"r")) != NULL){
		  yyin = tmp;
		 
	  }
	  if ((yyparse(&t)==0)) { 		/* yyparse calls yylex */
	    printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
	    
	    /* print the obtained tree */
	    if (t->left!=NULL) printf("Root symbol:: %c\n", t->car);	/* check if car at root */
	    printAST(t); printf("\n");
	    
	    //On récupère le nom du fichier sans l'extension 
	    char* nomFichier = strtok(argv[1],".");
	    //On lui ajoute l'extension .jsm 
	    char* nomExtension = strcat(nomFichier,".jsm");
	    printf("%s\n",nomExtension);
	    //suppression du fichier s'il existe deja
	    remove(nomExtension);
	    //On crée le code assembleur qui sera écrit dans le nouveau fichier
	    codeExtension(t, nomExtension); printf("\n");
	    //On ajoute à la fin du code : Halt 
	    FILE* fichier = NULL;
	    fichier = fopen(nomExtension,"a+");
	    fprintf(fichier,"Halt\n");
	    fclose(fichier);
    	    freeAST(t);
    	    
    	  }
	  fclose(tmp);
   }
   //Si l'on souhaite écrire l'expression sur le terminal
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
	    //On affiche le code assembleur sur le terminal
	    code(t); 
	    //On ajoute à la fin du code : Halt 
	    printf("Halt\n");	
	    freeAST(t);
	}
   }
   
  exit(EXIT_SUCCESS);
}

