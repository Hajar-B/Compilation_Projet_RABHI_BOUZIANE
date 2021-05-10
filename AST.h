#ifndef _AST_H_
#define _AST_H_
#include <stdbool.h>
/* unary-and-binary tree structure */
struct _tree {
  char* car;                    /* char for arithmetic operation */
  float val;			/* float  for value */
  char* boo;
  char* ide;
  struct _tree* left;    	/* used for unary node but NULL if leaf */
  struct _tree* right;   	/* NULL if unary node or leaf*/
};

typedef struct _tree* AST;

char* chaine(char* c);

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char* car, AST left, AST right);

/* create an AST from a root value and one AST son */
AST newUnaryAST(char* car, AST son);

AST newBinaryASTide(char* car, char* ide, AST son);

/* create an AST leaf from a value */
AST newLeafAST(float val);

/* create an AST leaf from a value */
AST newLeafASTb(char* chaine);

/* create an AST leaf from a value */
AST newLeafASTide(char* chaine);

/* create an AST leaf from a value */
AST newLeafASTaffect(char* chaine);

/* delete an AST */
void freeAST(AST t);

/* affichage du code assembleur dans un fichier .jsm */
void codeExtension(AST t, char* file);

/* print postfix without file*/
void code(AST t);

/* fonction qui va déterminer l'opération pour la fonction code */
void affichage(AST t);

/* print an AST*/
void printAST(AST t);

#endif // !_AST_H_
