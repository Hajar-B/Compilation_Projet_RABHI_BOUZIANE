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
    
    /*if(left && right && !strcmp(car)
    	t->taille = 1 + left->taille + right->taille;*/
    	/*
    if(left && right && !strcmp(car, "IfElse")){
    	if(
    	t->taille = 1 + left->right->taille + right->taille;
    }*/
    
    if(left && right && !strcmp(car, "If")){
    	printf("%s\n", car);
    	if(right->car && !strcmp(right->car,"IfElse"))
    		t->taille = 1+ 2 + right->left->left->taille + right->left->right->taille + right->right->taille;
    	else
    		t->taille = 1 + right->taille;		
    }
    else if(left && !right && !strcmp(car, "Else")){
    	printf("%s\n", car);
    	if(left->car && !strcmp(left->car,";"))
    		t->taille = 0;
    	if(left->car && !strcmp(left->car,"IfElse"))
    		t->taille = 1+ 2 + left->left->left->taille + left->left->right->taille + left->right->taille;	
    	if(left->car && !strcmp(left->car,";"))
    		t->taille = 0;	
    }
    else if(left && !right){
    	/*if(left->car && !strcmp(left->car,";"))
    		t->taille = 0;	
    	else */
    		t->taille = 1 + left->taille;
    }
    else {
    	t->taille = 1 + left->taille + right->taille;
    	
    }
    	
    /*
    if(!t->left && !t->right)
    	t->taille = 1;
    else if(t->left && !t->right && strcmp(car, "IfElse")){
   	if(!strcmp(car, "If"))
   		t->taille = 1;
   	else
    		t->taille = 1 + left->taille;
    	
    }
    else
    	t->taille = 1 + left->taille + right->taille;*/
   
  } else printf("MALLOC! ");
  return t;
}


/*printf("--car = %s\n",car);
        printf("left->right->car = %s\n",left->right->car);
    	if(!strcmp(left->right->car, "IfElse")){
    		t->taille = 2 + left->right->left->left->taille + left->right->left->right->taille + left->right->right->taille;
    	}
    	else*/


 /*
    if(t->right != NULL)
    	if(!strcmp(t->car,"If") && strcmp(t->car,"IfElse")){
	    	t->taille = 2 + right->taille;
    	}
   	else
   		t->taille = 1 + left->taille + right->taille;	 
    else 
    	t->taille = 1 + left->taille;
   
    if(t->right != NULL && t->right->car && !strcmp(t->right->car,"IfElse"))
   	 t->taille -= 1; 
    else if(t->left != NULL && t->left->car && !strcmp(t->left->car,"IfElse"))
    	 t->taille -= 1;   
    */
/* create an AST from a root value and one AST son */
AST newUnaryAST(char* car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

AST newUnaryASTide(char* ide, char* incre){
	return newBinaryASTide(incre, ide, NULL);
}

/* create an AST from a root value, a variable and one AST son */
AST newBinaryASTide(char* car, char* ide, AST son)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){
    t->ide = chaine(ide);
    if(son != NULL)
   	 t->taille = 1 + son->taille;
    else{ 
    	if(ide && !strcmp(car,"++"))
    		t->taille = 3;
    	else
    		t->taille = 1;
    }
    t->car=car;
    t->boo = NULL;
    t->left= son;
    t->right= NULL;
  } else printf("MALLOC! ");
  return t;
}



/* create an AST leaf from a value */
AST newLeafAST(char* val)
{
  
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */  
    t->val=chaine(val);
    t->car = NULL;
    if(val && strcmp(t->val,";"))
        t->taille = 1;
    else
    	t->taille = 0;
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
    else
    	t->boo="NaN";
    t->taille = 1;
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
    char c[11] = {'+','*','-','/','<','>','=','!',';','(',')'};
    char* ch;
    ch = strtok(chaine,c);
    t->ide=ch;
    t->taille = 1;
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
    		 if(strcmp(t->val,";")){
			char c[9] = {'+','*','/','<','>','=','!',';'};
			char c2[9] = {'+','*','-','/','<','>','=','!',';'};
			
			if(!strstr(t->val,"e-"))
	  			strtok(t->val,c2);
	  		else
	  			strtok(t->val,c);
		    	printf(":%s: ",t->val);
		   }
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

//On extrait la variable d'une chaine de caractère suivi d'un "="
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


/* postfix print an AST with a file

On ouvre le fichier en écriture. On parcourt l'arbre en affichant le fils gauche puis droit puis la racine. Si le noeud courant est :
- une feuille alors on écrit l'instruction CsteNb dans le fichier
- un noeud qui ne possède qu'un fils on écrit l'instruction NegaNb
- un noeud qui possède deux fils alors on va chercher à quelle opération il fait référence : '+' pour AddiNb, '*' pour MultNb et '-' pour SubiNb. 

On ferme le fichier.

*/ 
void codeExtension(AST t, char* file){
	
	
    if (t->left!=NULL){
    	if(!strcmp(t->car,"Else")){
	    	FILE* fichier = NULL;
		fichier = fopen(file,"a+");
	    	fprintf(fichier,"Jump %d \n",t->taille);
	    	fclose(fichier);
	}
    	codeExtension(t->left,file); 
    	
    }
    if (t->right!=NULL){ 
    	if(!strcmp(t->car,"If")){
    	       FILE* fichier = NULL;
	       fichier = fopen(file,"a+");
	       fprintf(fichier,"ConJmp %d \n",t->taille);
	       fclose(fichier);
	} 
    	codeExtension(t->right,file);
    }
   
    if(t->left == NULL){
    	if(t->boo == NULL && (t->ide == NULL)){
    		if(strcmp(t->val,";")){
	    		char c[9] = {'+','*','/','<','>','=','!',';'};
			char c2[9] = {'+','*','-','/','<','>','=','!',';'};
			
			if(!strstr(t->val,"e-"))
	  			strtok(t->val,c2);
	  		else
	  			strtok(t->val,c);
	  		FILE* fichier = NULL;
			fichier = fopen(file,"a+");
	  		fprintf(fichier,"CsteNb %s \n",t->val);
	  		fclose(fichier);
	  	}
    	}
	else if (t->ide == NULL){
		if(strcmp(t->boo,"NaN")){
			FILE* fichier = NULL;
	        	fichier = fopen(file,"a+");
			fprintf(fichier,"CsteBo %s \n",t->boo);
			fclose(fichier);
		}
	}
	else if (t->boo == NULL) {
		if(strstr(t->ide, "++")){
			strtok(t->ide,"++");
			FILE* fichier = NULL;
	        	fichier = fopen(file,"a+");
			fprintf(fichier,"GetVar %s\n",t->ide);
			fprintf(fichier,"CstNb 1\n");
			fprintf(fichier,"AddiNb\n");
			fprintf(fichier,"SetVar %s\n", t->ide);
			fclose(fichier);
		}
		else{
			FILE* fichier = NULL;
	        	fichier = fopen(file,"a+");
			fprintf(fichier,"GetVar %s\n",t->ide); 
			fclose(fichier);
		}
	} 	
    } 
    else if (t->left != NULL && (t->right == NULL)){
    	if(strcmp(t->car, "-") == 0){
    		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
    		fprintf(fichier,"NegaNb \n");
    		fclose(fichier);
    	}
    	else if (strcmp(t->car, "!") == 0){
    		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
    		fprintf(fichier,"Not \n");
    		fclose(fichier);
    	}
    	else if (!strcmp(t->car, "=") && t->ide != NULL) {
    		strtok(t->ide,"=");
    		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
    		fprintf(fichier,"SetVar %s \n",t->ide);
    		fclose(fichier); 
    	}
    } 
    else {
    	if(!strcmp(t->car,"+")){
    		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
		fprintf(fichier,"AddiNb\n");
		fclose(fichier);
	}
	if(!strcmp(t->car,"*")){
		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
		fprintf(fichier,"MultNb\n");
		fclose(fichier);
	}
	if(!strcmp(t->car,"-")){
		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
		fprintf(fichier,"SubiNb\n");
		fclose(fichier);
	}
	if(!strcmp(t->car,"/")){
		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
		fprintf(fichier,"DiviNb\n");
		fclose(fichier);
	}
	if(!strcmp(t->car,"==")){
		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
		fprintf(fichier,"Equals\n");
		fclose(fichier);
	}
	if(!strcmp(t->car,"!=")){
		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
		fprintf(fichier,"NoEql\n");
		fclose(fichier);
	}
	if(!strcmp(t->car, ">=")){
		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
		fprintf(fichier,"GrEqNb\n");
		fclose(fichier);
	}
	if(!strcmp(t->car,">")){
		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
		fprintf(fichier,"GrStNb\n");
		fclose(fichier);
	}
	if(!strcmp(t->car, "<=")){
		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
		fprintf(fichier,"LoEqNb\n");
		fclose(fichier);
	}
	if(!strcmp(t->car,"<")){
		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
		fprintf(fichier,"LoStNb\n");
		fclose(fichier);
	}
    }
    
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
    	//printf("car 2 %s \n",t->car);
    	if(!strcmp(t->car,"Else")){
    		//t->taille = t->taille + 1 + t->left->taille;
	    	printf("Jump %d \n",t->taille);
	    	printf("%d\n", t->taille);
	}
    	code(t->left);
    }
    if (t->right!=NULL){ 
    	if(!strcmp(t->car,"If")){
    		printf("ConJmp %d \n",t->taille); 
		printf("*%d\n", t->taille);
    	/*
    	//	if(!strcmp(t->right->car, "IfElse")){
    			//t->taille = t->right->left->taille;
    			//t->taille = 2 + t->taille + t->right->left->taille + t->right->right->taille;
    			//printf("***%s\n",t->right->left->car);
    			//printf("***%s\n",t->right->right->car);
		    	printf("ConJmp %d \n",t->taille); 
		    	printf("--%d\n", t->taille);
		}
		else{
	    		//t->taille = t->taille + 1 + t->left->taille;
		    	printf("ConJmp %d \n",t->taille); 
		    	printf("*%d\n", t->taille);
		}*/
	}
    	code(t->right);
    	
    }
    
    if(t->left == NULL){

	if(t->boo == NULL && (t->ide == NULL)){
		if(strcmp(t->val,";")){
			char c[9] = {'+','*','/','<','>','=','!',';'};
			char c2[9] = {'+','*','-','/','<','>','=','!',';'};
			
			if(!strstr(t->val,"e-"))
	  			strtok(t->val,c2);
	  		else
	  			strtok(t->val,c);
		    	printf("CsteNb %s \n",t->val);
		    	printf("%d\n", t->taille);
		 }
	}
	    	
	else if (t->ide == NULL ){
		if(strcmp(t->boo,"NaN")){
			printf("CsteBo %s \n",t->boo); 
			printf("%d\n", t->taille);
		}
	}
	else if (t->boo == NULL )  {
		
		if(strstr(t->ide, "++")){
			strtok(t->ide,"++");
			printf("GetVar %s\n",t->ide);
			printf("CstNb 1\n");
			printf("AddiNb\n");
			printf("SetVar %s\n", t->ide);
			printf("%d\n", t->taille);
		}
		else{
			printf("GetVar %s \n",t->ide);
			printf("%d\n", t->taille);
		}
	}
    } 	  
    else if (t->left != NULL && (t->right == NULL)){
    	if(strcmp(t->car, "-") == 0){
    		printf("NegaNb \n");
    		//t->taille = t->taille + t->left->taille;
    		printf("%d\n", t->taille);
    	}
    	else if (strcmp(t->car, "!") == 0){
    		printf("Not \n");
    		//t->taille = t->taille + t->left->taille;
    		printf("%d\n", t->taille);
    	}
    	else if (!strcmp(t->car, "=") && t->ide != NULL) {
    		strtok(t->ide,"=");
    		printf("SetVar %s \n",t->ide); 
    		//t->taille = t->taille + t->left->taille;
    		printf("%d\n", t->taille);
    	}
    } 
    else{ 
    		affichage(t);
    	
    }
}


//fonction qui va déterminer l'opération pour la fonction code
void affichage(AST t){
	if(!strcmp(t->car,"+")){
		printf("AddiNb\n");
		//t->taille = 1+t->left->taille + t->right->taille;
		printf("%d\n", t->taille);
	}
	if(!strcmp(t->car,"*")){
		printf("MultNb\n");
		//t->taille = 1+t->left->taille + t->right->taille;
		printf("%d\n", t->taille);
	}
	if(!strcmp(t->car,"-")){
		printf("SubiNb\n");
		//t->taille = 1+t->left->taille + t->right->taille;
		printf("%d\n", t->taille);
	}
	if(!strcmp(t->car,"/")){
		printf("DiviNb\n");
		//t->taille = 1+t->left->taille + t->right->taille;
		printf("%d\n", t->taille);
	}
	if(!strcmp(t->car,"==")){
		printf("Equals\n");
		//t->taille = 1+t->left->taille + t->right->taille;
		printf("%d\n", t->taille);
	}
	if(!strcmp(t->car,"!=")){
		printf("NoEql\n");
		//t->taille = 1+t->left->taille + t->right->taille;
		printf("%d\n", t->taille);
	}
	if(!strcmp(t->car, ">=")){
		printf("GrEqNb\n");
		//t->taille = 1+t->left->taille + t->right->taille;
		printf("%d\n", t->taille);
	}
	if(!strcmp(t->car,">")){
		printf("GrStNb\n");
		//t->taille = 1+t->left->taille + t->right->taille;
		printf("%d\n", t->taille);
	}
	if(!strcmp(t->car, "<=")){
		printf("LoEqNb\n");
		//t->taille = 1+t->left->taille + t->right->taille;
		printf("%d\n", t->taille);
	}
	if(!strcmp(t->car,"<")){
		printf("LoStNb\n");
		//t->taille = 1+t->left->taille + t->right->taille;
		printf("%d\n", t->taille);
	}
	
}

