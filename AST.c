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
AST newLeafAST(double val)
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
    if (t->left==NULL) printf(":%f: ",t->val); else printf(":%c: ",t->car);
    printAST(t->right);
    printf("] ");
  }
}


void codeExtension(AST t, char* file){
	FILE* fichier = NULL;
	fichier = fopen(file,"a+");

    if (t->left!=NULL){ 
    	codeExtension(t->left,file); 
    }
    if (t->right!=NULL){ 
    	codeExtension(t->right,file);
    }
   
    if(t->left == NULL) fprintf(fichier,"CsteNb %f \n",t->val); 
    else if (t->left != NULL && (t->right == NULL)) fprintf(fichier,"NegaNb \n");
    else {
    	switch(t->car){
			case '+' :
				fprintf(fichier, "AddiNb\n"); break;
			case '*' :
				fprintf(fichier, "MultNb\n"); break;
			case '-' :
				fprintf(fichier, "SubiNb\n"); break;
			case '/' :
				fprintf(fichier, "DiviNb\n"); break;
			default : fprintf(fichier," "); break;
		}	
    }
	fclose(fichier);
}


/* postfix print an AST*/  
void code(AST t)
{	
    if (t->left!=NULL){ 
    	code(t->left); 
    }
    if (t->right!=NULL){ 
    	code(t->right);
    }
   
    if(t->left == NULL) printf("CsteNb %f \n",t->val); 
    else if (t->left != NULL && (t->right == NULL)) printf("NegaNb \n");
    else affichage(t->car);
}


void affichage(char t){
	switch(t){
		case '+' :
			printf("AddiNb\n"); break;
		case '*' :
			printf("MultNb\n"); break;
		case '-' :
			printf("SubiNb\n"); break;
		case '/' :
			printf("DiviNb\n"); break;
		default : printf(" "); break;
	}	

}

