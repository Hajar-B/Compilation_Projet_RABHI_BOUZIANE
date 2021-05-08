# Fragment c0.2

Réalisé par : BOUZIANE Hajar

## Description 

1. **lexeur.l** : 
* le fichier *parseur.tab.h* est inclu car il permet de définir les tokens NOMBRE, PT_VIRG, FLOAT, BOOLEAN, EQUALS, NOTEQL, GREQ et LOEQ.
* On a ajouté un type int pour notre token NOMBRE
* On a ajouté un type double pour notre token FLOAT
* On a ajouté un type char* pour notre token BOOLEAN
* Pour chaque expression régulière, on renvoie le token qui lui est associé. La première expression régulière reconnaît :
  * un nombre, 
  * un flottant, 
  * un booléen,
  * une égalité,
  * une inégalité, 
  * un 'supérieur ou égale', 
  * un 'inférieur ou égale',
  * un point virgule.

2. **parseur.y** :
- on prend l'adresse de l'AST vide et que l'on modifiera plus tard
- par défaut les tokens de bison ont le type int mais puisque l'on
doit implémenter la structure de l'arbre syntaxique, les flottants et les booléens, alors on utilise le %union
- on définit un type expression, il permet de spécifier le type qui sera généré dans l'AST. En d'autres termes expression va construire un AST de *exp*.
- on définit 8 tokens : NOMBRE, FLOAT, BOOLEAN, PT_VIRG, EQUALS, NOTEQL, GREQ et LOEQ.
- on définit les règles d'associativité gauche avec %left
- on définit les règles de priorité : les opérations booléennes (étant les moins prioritaires) sont définies en premier. S'en suit du '+' et du '-' car ils sont moins prioritaires que le '*' et le '/' (que l'on a donc définit dans un troisième temps). Pour finir, comme le '!' est prioritaire sur toutes les précédentes opérations, il a été défini en dernier.
- on définit une balise MOINSU pour signifier qu'il a une autre priorité que le '-'
- Par conséquent, on a mis à jour la grammaire sans oublier d'ajouter les opérations '<' et '>'.

3. **AST.h**:
- on a modifié le type du champ val pour que ce ne soit plus des entiers mais uniquement des flottants.
- de plus, on ajouté un champ *boo* à la structure de notre AST qui fera référence aux booléens.

3. **AST.c**:
- suite à la précédente modification on a modifié les fonctions pour qu'elles affichent des flottants. 
- on a ajouté la fonction newLeafASTb(char* boolean) qui permettra d'ajouter une feuille contenant un booléen.
- code(AST t) et affichage(char* t): ces fonctions vont afficher le code assembleur lorsqu'aucun fichier n'est donné en paramètre lors de l'exécution du main
- codeExtension(AST t, char* file) : cette fonction va écrire dans le fichier file (qui sera avec l'extension .jsm) le code assembleur.

4. **main.c**:
- programme exécutable qui va parser le contenu d'un fichier.
- on peut executer de deux manières le main : soit en mettant en argument un fichier soit en saisissant l'expression sur le terminal.
- si l'on choisit d'exécuter avec un fichier, on crée un fichier avec le même nom mais avec l'extension .jsm 
- affiche un message indiquant si la synthaxe de ce contenu est correcte ou non.

5. **test.txt**:
- fichier qui contient une expression JS à parser.
- on a testé les expressions suivantes: 


1+2==3;

- CsteNb 1.000000 
- CsteNb 2.000000 
- AddiNb
- CsteNb 3.000000 
- Equals
- Halt

=> ok

(1+2)==3;

- CsteNb 1.000000 
- CsteNb 2.000000 
- AddiNb
- CsteNb 3.000000 
- Equals
- Halt

=> ok

1+(2==3); 

- CsteNb 1.000000 
- CsteNb 2.000000 
- CsteNb 3.000000 
- Equals
- AddiNb
- Halt

=> ok

True+3!=5.123; 

- CsteBo True 
- CsteNb 3.000000 
- AddiNb
- CsteNb 5.123000 
- NoEql
- Halt

=>ok

False<=33333/33; 

- CsteBo False 
- CsteNb 33333.000000 
- CsteNb 33.000000 
- DiviNb
- LoEqNb
- Halt


=> ok

0-32<(7+7.000000);

- CsteNb 0.000000 
- CsteNb 32.000000 
- SubiNb
- CsteNb 7.000000 
- CsteNb 7.000000 
- AddiNb
- LoStNb
- Halt

=> ok

!!True; 

- CsteBo True 
- Not 
- Not 
- Halt


=> ok

True*34+1==False-!True; 

- CsteBo True 
- CsteNb 34.000000 
- MultNb
- CsteNb 1.000000 
- AddiNb
- CsteBo False 
- CsteBo True 
- Not 
- SubiNb
- Equals
- Halt


=> ok

!(True==False); 

- CsteBo True 
- CsteBo False 
- Equals
- Not 
- Halt

=> ok

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


