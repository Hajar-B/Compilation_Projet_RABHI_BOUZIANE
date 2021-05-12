# Fragment c2.0

Réalisé par : Sohayla RABHI

## Description 

1. **lexeur.l** : 
* le fichier *parseur.tab.h* est inclu car il permet de définir les tokens NAN, NUMBER, IDENT, BOOLEAN, IF, ELSE, EQUALS, NOTEQL, GREQ, LOEQ, INCRE et PT_VIRG. 
* On a ajouté un type char* pour notre token NUMBER
* On a ajouté un type char* pour nos tokens BOOLEAN et NAN
* On a ajouté un type char* pour notre token IDENT
* Pour chaque expression régulière, on renvoie le token qui lui est associé. Les expressions régulières reconnaîssent :
  * un 'Not a Number',
  * un number, 
  * une variable,
  * un booléen,
  * un 'If',
  * un 'Else",
  * une égalité,
  * une inégalité, 
  * un 'supérieur ou égale', 
  * un 'inférieur ou égale',
  * un incrémentation,
  * un point virgule. 
* une expression régulière associée à ces tokens ont été ajoutées.
* une expression régulière a été créé pour des commentaires unilignes.
* une autre expression régulière a été créé pour des commentaires multilignes.

2. **parseur.y** :
- on utilise %start car maintenant le non-terminal principal n'est plus expression mais programme.
- on définit trois types : un type expression, un type programme_ast et un autre type commande_ast (non-terminaux). En d'autres termes ces non-terminaux vont construire un AST de *exp*.
- on définit 12 tokens : NAN, NUMBER, IDENT, BOOLEAN, IF, ELSE, EQUALS, NOTEQL, GREQ, LOEQ, INCRE et PT_VIRG. Notons que les opérations "==", "!=", "<=", ">=" et "++" sont des multisymboles d'où la création de leur token.
- on définit les règles d'associativité gauche grâce au %left.
- on définit les règles de priorités : L'affection '=' est définie en premier car elle est moins prioritaire que toutes les autres opérations. Les opérations booléennes sont définies en deuxième. S'en suit du '+' et du '-' car ils sont moins prioritaires que le '*' et le '/' (que l'on a donc défini dans un troisième temps). Comme le '++' est prioritaire sur toutes les précédentes opérations, il a été défini après le '!'.
- on définit une balise MOINSU pour sigifier qu'il a une autre priorité que la soustraction '-'.
- on définit une nouvelle ligne à notre non-terminal commande qui décrit une condition If Else.
- on a ajouté un noeud prog, pour y spécifier dans l'AST les suites de commandes. 


3. **AST.h**:
- on a modifié le type du champ val pour que ce ne soit plus des entiers mais uniquement des flottants.
- on a ajouté un champ *boo* à la structure de notre AST qui fera référence aux booléens.
- on a ajouté un champ *ide* à la structure de notre AST qui fera référence aux variables.
on a également ajouté un champ *taille* à la structure de notre AST qui fera référence à la taille du code généré et qui sera utlisé pour les conditionnelles.


4. **AST.c**:
- suite à la précédente modification on a modifié les fonctions pour qu'elles affichent des flottants. 
- on a ajouté la fonction newLeafASTb(char* boolean) qui permettra d'ajouter une feuille contenant un booléen.
- code(AST t) et affichage(char* t): ces fonctions vont afficher le code assembleur lorsqu'aucun fichier n'est donné en paramètre lors de l'exécution du main
- codeExtension(AST t, char* file) : cette fonction va écrire dans le fichier file (qui sera avec l'extension .jsm) le code assembleur.
- Une fonction newBinaryASTide(char* car, char* ide, AST son) a été ajouté, elle crée un arbre où la racine ne possède qu'un fils. Par exemple, pour l'expression y=x+1; la racine stockera le "y=" quand au fils il correspondra au sous arbre qui contiendra l'expression x+1.
- Une autre fonction newLeafASTide(char* chaine) qui va créer la feuille qui contiendra une variable;
- newUnaryASTide(char* ide, char* incre) a ensuite été ajouté. Elle permet de créer une feuille qui sera composée de l'opération "++" ainsi que de la variable qu'elle incrémente.
- Pour toutes fonctions qui vont générer des feuilles on va initialiser la taille à 1. Il y a une spécificité pour l'opération d'incrémentation, on doit lui ajouter 4 lignes.
- Pour les fonctions qui génèrent des arbres (avec un ou deux fils) on va initialiser la taille à : 1 + taille du fils gauche + taille du fils droit. Si l'un deux est NULL on lui donne la taille 0 dans cette formule. Lorsqu'on passe par un noeud qui est un 'If' on initialise la taille à : 2 + la taille de son fils droit. De plus lorsqu'on passe par le noeud qui contient 'IfElse' on décrémente de 1 car lorsqu'on crée un 'if_then_else' on crée un arbre binaire 'IfElse' qui est lui-même composé d'un arbre binaire 'If' et et d'un arbre unaire 'Else' ce qui fausse la taille de 1.

5. **main.c**:
- programme exécutable qui va parser le contenu d'un fichier.
- on peut executer de deux manières le main : soit en mettant en argument un fichier soit en saisissant l'expression sur le terminal.
- si l'on choisit d'exécuter avec un fichier, on crée un fichier avec le même nom mais avec l'extension .jsm 
- affiche un message indiquant si la synthaxe de ce contenu est correcte ou non.


6. **test.txt**:

If(x)If(y)y++;Elsey=y-1;Elsex=x-1;

- Parsing:: syntax OK


*** 

- GetVar x
- ConJmp 12 
- GetVar y
- ConJmp 5 
- GetVar y
- CstNb 1
- AddiNb
- SetVar y
- Jump 4 
- GetVar y
- CsteNb 1 
- SubiNb
- SetVar y 
- Jump 4 
- GetVar x
- CsteNb 1 
- SubiNb
- SetVar x 
- Halt

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

