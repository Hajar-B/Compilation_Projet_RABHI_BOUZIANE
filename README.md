<<<<<<< HEAD
# Fragment c1.3
=======
# Fragment p2.1
>>>>>>> parser

Réalisé par : Hajar BOUZIANE

## Description 

1. **lexeur.l** : 
- le fichier *parseur.tab.h* est inclu car il permet de définir les tokens NAN, NUMBER, IDENT, BOOLEAN, IF, ELSE, EQUALS, NOTEQL, GREQ, LOEQ, INCRE et PT_VIRG. 
- une expression régulière associée à ces tokens ont été ajoutées.
- une expression régulière a été créé pour des commentaires unilignes.
- une autre expression régulière a été créé pour des commentaires multilignes.


2. **parseur.y** :
- on utilise %start car maintenant le non-terminal principal n'est plus expression mais programme.
- on définit 12 tokens : NAN, NUMBER, IDENT, BOOLEAN, IF, ELSE, EQUALS, NOTEQL, GREQ, LOEQ, INCRE et PT_VIRG. Notons que les opérations "==", "!=", "<=", ">=" et "++" sont des multisymboles d'où la création de leur token.
- on définit les règles d'associativité gauche grâce au %left.
- on définit les règles de priorités : L'affection '=' est définie en premier car elle est moins prioritaire que toutes les autres opérations. Les opérations booléennes sont définies en deuxième. S'en suit du '+' et du '-' car ils sont moins prioritaires que le '*' et le '/' (que l'on a donc défini dans un troisième temps). Comme le '++' est prioritaire sur toutes les précédentes opérations, il a été défini après le '!'.
- on définit une balise MOINSU pour sigifier qu'il a une autre priorité que la soustraction '-'.
- on définit deux nouvelles lignes à notre non-terminal 'commande':
   * une qui décrit une condition If Else.
   * une autre qui décrit une commande vide
   * et enfin, une qui décrit un programme (une suite de commandes)
- par conséquent, on a mis à jour la grammaire.


3. **test.txt**:

If(x<=y){x=3e-3;If(c==y)y=x+0.1;Else{y++;}}Elsey=-2;

- Parsing:: syntax OK

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



