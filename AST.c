#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char* car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->car=car;
    t->boo = NULL;
    t->left=left;
    t->right=right;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char* car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

/* create an AST leaf from a value */
AST newLeafAST(float val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val=val;
    t->car = NULL;
    t->boo= NULL;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}

AST newLeafASTb(char* boolean){
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
  
    if(strcmp(boolean,"True")==0)
    	t->boo="True";
    if(strcmp(boolean,"False")==0)
    	t->boo="False";
    t->car=NULL;
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
    if (t->left==NULL) {
    	if(t->boo == NULL)
	    	printf(":%f: ",t->val);
	else
		printf(":%s: ",t->boo);   	
    }
    else printf(":%s: ",t->car);
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
   
    if(t->left == NULL){
    	if (t->left==NULL) {
	    	if(t->boo == NULL)
		    	fprintf(fichier,"CsteNb %f \n",t->val);
		else
			fprintf(fichier,"CsteBo %s \n",t->boo);  
	} 	
    } 
    
    else if (t->left != NULL && (t->right == NULL)){
    	if(strcmp(t->car, "-") == 0)
    		fprintf(fichier,"NegaNb \n");
    	else if (strcmp(t->car, "!") == 0)
    		fprintf(fichier,"Not \n");
    } 
    else {
    	if(!strcmp(t->car,"+"))
		fprintf(fichier,"AddiNb\n");
	if(!strcmp(t->car,"*"))
		fprintf(fichier,"MultNb\n");
	if(!strcmp(t->car,"-"))
		fprintf(fichier,"SubiNb\n");
	if(!strcmp(t->car,"/"))
		fprintf(fichier,"DiviNb\n");
	if(!strcmp(t->car,"=="))
		fprintf(fichier,"Equals\n");
	if(!strcmp(t->car,"!="))
		fprintf(fichier,"NoEql\n");
	if(!strcmp(t->car, ">="))
		fprintf(fichier,"GrEqNb\n");
	if(!strcmp(t->car,">"))
		fprintf(fichier,"GrStNb\n");
	if(!strcmp(t->car, "<="))
		fprintf(fichier,"LoEqNb\n");
	if(!strcmp(t->car,"<"))
		fprintf(fichier,"LoStNb\n");
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
    if(t->left == NULL){
    	if (t->left==NULL) {
	    	if(t->boo == NULL)
		    	printf("CsteNb %f \n",t->val);
		else
			printf("CsteBo %s \n",t->boo);  
	} 	
    }    
    else if (t->left != NULL && (t->right == NULL)){
    	if(strcmp(t->car, "-") == 0)
    		printf("NegaNb \n");
    	else if (strcmp(t->car, "!") == 0)
    		printf("Not \n");
    } 
    else affichage(t->car);
}

//fonction qui va déterminer l'opération pour la fonction code
void affichage(char* t){
	if(!strcmp(t,"+"))
		printf("AddiNb\n");
	if(!strcmp(t,"*"))
		printf("MultNb\n");
	if(!strcmp(t,"-"))
		printf("SubiNb\n");
	if(!strcmp(t,"/"))
		printf("DiviNb\n");
	if(!strcmp(t,"=="))
		printf("Equals\n");
	if(!strcmp(t,"!="))
		printf("NoEql\n");
	if(!strcmp(t, ">="))
		printf("GrEqNb\n");
	if(!strcmp(t,">"))
		printf("GrStNb\n");
	if(!strcmp(t, "<="))
		printf("LoEqNb\n");
	if(!strcmp(t,"<"))
		printf("LoStNb\n");
}
