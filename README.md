# Fragment c0.1

Réalisé par : Sohayla RABHI

## Description 

1. **lexeur.l** : 
- le fichier *parseur.tab.h* est inclu car il permet de définir les tokens NUMBER, PT_VIRG et FLOAT
- On a ajouté un type int pour notre token NUMBER
- On a ajouté un type double pour notre token FLOAT
- Pour chaque expression régulière, on renvoie le token qui lui est associé. La première expression régulière reconnaît un nombre, la seconde reconnaît un point virgule et la troisième un flottant.


2. **parseur.y** :
- on prend l'adresse de l'AST vide et que l'on modifiera plus tard
- par défaut les tokens de bison ont le type int mais puisque l'on
doit implémenter la structure de l'arbre syntaxique et les flottants alors on utilise le %union
- on définit un type expression, il permet de spécifier le type qui sera généré dans l'AST. En d'autres termes expression va construire un AST de exp.
- on définit 3 tokens : NUMBER, PT_VIRG et FLOAT
- on définit les règles d'associativité gauche avec %left
- on définit les règles de priorité : '*' et '/' sont prioritaires sur '+' et '-' car ils sont définis après le '+' et le '-'.
- on définit une balise MOINSU pour signifier qu'il a une autre priorité que le '-'
- on définit la grammaire : pour chaque ligne on lui associe une règle qui est de créer un noeud. Ce dernier peut être : soit une feuille, soit un noeud avec un seul fils, ou un noeud avec deux fils.

3. **AST.h**:
- on a modifié le type du champ val pour que ce ne soit plus des entiers mais uniquement des flottants.

3. **AST.c**:
- suite à la précédente modification on a modifié les fonctions pour quelles affichent des flottants. 
- code(AST t) et affichage(char t): ces fonctions vont afficher le code assembleur lorsqu'aucun fichier n'est donné en paramètre lors de l'execution du main
- codeExtension(AST t, char* file) : cette fonction va écrire dans le fichier file (qui sera avec l'extension .jsm) le code assembleur.


4. **main.c**:
- programme exécutable qui va parser le contenu d'un fichier.
- on peut executer de deux manières le main : soit en mettant en argument un fichier soit en saisissant l'expression sur le terminal.
- si l'on choisit d'exécuter avec un fichier, on crée un fichier avec le même nom de fichier mais avec l'extension .jsm 
- affiche un message indiquant si la synthaxe de ce contenu est correcte ou non.

5. **test.txt**:
- fichier qui contient une expression JS à parser.
- on a tester les expressions suivantes: 

34//78;		=> error

34/-/78;		=> error

3.;	=> error

-3.2*24/12-(3--1.0);   => ok

12/(-2+3);		=> ok

3.10/1.0555+97-2;	=> ok



## Comment compiler et exécuter ?

Pour compiler, lancer les commandes suivantes:

bison -d parseur.y

flex lexeur.l

gcc -o main main.c parseur.tab.c lex.yy.c

Pour exécuter, deux possibilités s'offrent à vous :

./main test.txt
(on ne peut écrire qu'une expression à la fois dans le fichier test.txt)

./main
(puis saisir sur le terminal une expression à parser)


