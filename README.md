# Frangment 0.0

Réalisé par : BOUZIANE Hajar

## Description 

1. **lexeur.l** : 
- le fichier *parseur.tab.h* est inclu car il permet de définir les tokens NUMBER et PT_VIRG
- Pour chaque expression régulière, on renvoie le token qui lui est associé. La première expression régulière reconnaît un nombre tandis que la seconde reconnaît un point virgule.

2. **parseur.y** :
- on définit 2 tokens : NUMBER et PT_VIRG
- on définit les règles d'associativité gauche avec %left
- on définit une balise MOINSU pour signifier qu'il a une autre priorité que le '-'
- on définit les règles de priorité : '*' est prioritaire sur '+' et '-' car il est défini après le '+' et le '-'.
- on définit la grammaire

3. **main.c**:
- programme exécutable qui va parser le contenu d'un fichier.
- affiche un message indiquant si la synthaxe de ce contenu est correcte ou non.

4. **test.txt**:
- fichier qui contient une expression JS à parser.
- on a tester les expressions suivantes: 
;       => error

(3+3;); => error

3*(-3--2; => error

3;      => OK

3+3;    => OK

(3+3);  => OK

-3;	=> OK

(-3);	=> OK

(-3--2); => OK

(-3*2); => OK

(-3-2); => OK

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

