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
    t->ide = NULL;
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

AST newUnaryASTide(char* ide, char* incre){
	return newBinaryASTide(incre, ide, NULL);
}

AST newBinaryASTide(char* car, char* ide, AST son)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){
    t->ide = chaine(ide);
    t->car=car;
    t->boo = NULL;
    t->left= son;
    t->right= NULL;
  } else printf("MALLOC! ");
  return t;
}


/* create an AST leaf from a value */
AST newLeafAST(float val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val=val;
    t->car = NULL;
    t->boo = NULL;
    t->ide = NULL;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}


AST newLeafASTb(char* chaine){
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
  
    if(strcmp(chaine,"True")==0)
    	t->boo="True";
    else if(strcmp(chaine,"False")==0)
    	t->boo="False";
    t->ide=NULL;
    t->car=NULL;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}

AST newLeafASTide(char* chaine){
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	
    t->boo = NULL;
    char c[9] = {'+','*','-','/','<','>','=','!',';'};
    char* ch;
    ch = strtok(chaine,c);
    t->ide=ch;
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
    	if(t->boo == NULL && (t->ide == NULL)){
	    	printf(":%f: ",t->val);
	}
	else if (t->ide == NULL)
		printf(":%s: ",t->boo); 
	else{
		if(strstr(t->ide, "++")){
			printf(":%s: ",t->ide);
		}
		else {
			if(strstr(t->ide, "++")){
				printf(":%s: ",t->ide);
			}
			else{
			 	char c[9] = {'+','*','-','/','<','>','=','!',';'};
			 	char* ch = strtok(t->ide,c);
			 	if(ch != NULL) printf(":%s: ",ch);
			 	else printf(":%s: ",t->ide);
			 }
		}
	 } 
	 
    }
    else if(t->ide != NULL && !t->val && t->boo == NULL){
    	printf(":%s: ",chaine(t->ide));
    }
    else printf(":%s: ",t->car);
    printAST(t->right);
    printf("] ");
  }
}

char* chaine(char* c){
	char* ch = (char*)malloc(strlen(c)*sizeof(char));
	for(int i = 0; i<strlen(c);i++){
		if(c[i] != '='){
			ch[i]=c[i];
		}		
		else{
		 	ch[i]=c[i];
			return ch;
		}
	}
	return ch;
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
   
    if(t->left == NULL){
    	if(t->boo == NULL && (t->ide == NULL))
		  fprintf(fichier,"CsteNb %f \n",t->val);
	else if (t->ide == NULL)
		fprintf(fichier,"CsteBo %s \n",t->boo);
	else if (t->boo == NULL) {
		if(strstr(t->ide, "++")){
			strtok(t->ide,"++");
			fprintf(fichier,"GetVar %s\n",t->ide);
			fprintf(fichier,"CstNb 1\n");
			fprintf(fichier,"AddiNb\n");
			fprintf(fichier,"SetVar %s\n", t->ide);
		}
		else
			fprintf(fichier,"GetVar %s\n",t->ide); 
	} 	
    } 
    
    else if (t->left != NULL && (t->right == NULL)){
    	if(strcmp(t->car, "-") == 0)
    		fprintf(fichier,"NegaNb \n");
    	else if (strcmp(t->car, "!") == 0)
    		fprintf(fichier,"Not \n");
    	else if (!strcmp(t->car, "=") && t->ide != NULL) {
    		strtok(t->ide,"=");
    		fprintf(fichier,"SetVar %s \n",t->ide); 
    	}
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


/* postfix print an AST*/  
void code(AST t)
{	
    if (t->left!=NULL){ 
    	code(t->left); 
    }
    if (t->right!=NULL){ 
    	code(t->right);
    }
    if(t->left == NULL){
	if(t->boo == NULL && (t->ide == NULL))
	    	printf("CsteNb %f \n",t->val);
	else if (t->ide == NULL)
		printf("CsteBo %s \n",t->boo); 
	else if (t->boo == NULL)  {
		if(strstr(t->ide, "++")){
			strtok(t->ide,"++");
			printf("GetVar %s\n",t->ide);
			printf("CstNb 1\n");
			printf("AddiNb\n");
			printf("SetVar %s\n", t->ide);
		}
		else
			printf("GetVar %s \n",t->ide);
	}
    } 	  
    else if (t->left != NULL && (t->right == NULL)){
    	if(strcmp(t->car, "-") == 0)
    		printf("NegaNb \n");
    	else if (strcmp(t->car, "!") == 0)
    		printf("Not \n");
    	else if (!strcmp(t->car, "=") && t->ide != NULL) {
    		strtok(t->ide,"=");
    		printf("SetVar %s \n",t->ide); 
    	}
    } 
    else affichage(t);
}

void affichage(AST t){
	if(!strcmp(t->car,"+"))
		printf("AddiNb\n");
	if(!strcmp(t->car,"*"))
		printf("MultNb\n");
	if(!strcmp(t->car,"-"))
		printf("SubiNb\n");
	if(!strcmp(t->car,"/"))
		printf("DiviNb\n");
	if(!strcmp(t->car,"=="))
		printf("Equals\n");
	if(!strcmp(t->car,"!="))
		printf("NoEql\n");
	if(!strcmp(t->car, ">="))
		printf("GrEqNb\n");
	if(!strcmp(t->car,">"))
		printf("GrStNb\n");
	if(!strcmp(t->car, "<="))
		printf("LoEqNb\n");
	if(!strcmp(t->car,"<"))
		printf("LoStNb\n");
}

