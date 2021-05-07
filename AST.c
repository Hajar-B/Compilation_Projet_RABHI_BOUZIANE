#include <stdio.h>
#include <stdlib.h>
#include "AST.h"

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->car=car;
    t->left=left;
    t->right=right;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

/* create an AST leaf from a value */
AST newLeafAST(int val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val=val;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}

/* delete an AST */
void freeAST(AST t)
{
  if (t!=NULL) {
    freeAST(t->left);
    freeAST(t->right);
    free(t);
  }
}

/* infix print an AST*/
void printAST(AST t)
{
  if (t!=NULL) {
    printf("[ ");
    printAST(t->left);
    /* check if node is car|val */
    if (t->left==NULL) printf(":%d: ",t->val); else printf(":%c: ",t->car);
    printAST(t->right);
    printf("] ");
  }
}

/* postfix print an AST with a file

On ouvre le fichier en écriture. On parcourt l'arbre en affichant le fils gauche puis droit puis la racine. Si le noeud courant est :
- une feuille alors on écrit l'instruction CsteNb dans le fichier
- un noeud qui ne possède qu'un fils on écrit l'instruction NegaNb
- un noeud qui possède deux fils alors on va chercher à quelle opération il fait référence : '+' pour AddiNb, '*' pour MultNb et '-' pour SubiNb. 

On ferme le fichier.

*/ 
void codeExtension(AST t, char* file){
	FILE* fichier = NULL;
	fichier = fopen(file,"a+");

    if (t->left!=NULL){ 
    	codeExtension(t->left,file); 
    }
    if (t->right!=NULL){ 
    	codeExtension(t->right,file);
    }
   
    if(t->left == NULL) fprintf(fichier,"CsteNb %d \n",t->val); 
    else if (t->left != NULL && (t->right == NULL)) fprintf(fichier,"NegaNb \n");
    else {
    	switch(t->car){
			case '+' :
				fprintf(fichier, "AddiNb\n"); break;
			case '*' :
				fprintf(fichier, "MultNb\n"); break;
			case '-' :
				fprintf(fichier, "SubiNb\n"); break;
			default : fprintf(fichier," "); break;
		}	
    }
	fclose(fichier);
}


/* postfix print an AST without file

On parcourt tout d'abord l'arbre en affichant le fils gauche puis droit puis la racine. Si le noeud courant est :
- une feuille alors on affiche l'instruction CsteNb
- un noeud qui ne possède qu'un fils on affiche l'instruction NegaNb
- un noeud qui possède deux fils alors on va chercher à quelle opération il fait référence : '+' pour AddiNb, '*' pour MultNb et '-' pour SubiNb. 

*/  
void code(AST t)
{	
    if (t->left!=NULL){ 
    	code(t->left); 
    }
    if (t->right!=NULL){ 
    	code(t->right);
    }
   
    if(t->left == NULL) printf("CsteNb %d \n",t->val); 
    else if (t->left != NULL && (t->right == NULL)) printf("NegaNb \n");
    else affichage(t->car);
}

//fonction qui va déterminer l'opération pour la fonction code
void affichage(char t){
	switch(t){
		case '+' :
			printf("AddiNb\n"); break;
		case '*' :
			printf("MultNb\n"); break;
		case '-' :
			printf("SubiNb\n"); break;
		default : printf(" "); break;
	}	

}

