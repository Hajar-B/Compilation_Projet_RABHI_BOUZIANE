# Fragment p1.0

Réalisé par : Sohayla RABHI

## Description 

1. **lexeur.l** : 
- le fichier *parseur.tab.h* est inclu car il permet de définir les tokens NOMBRE, FLOAT, IDENT, BOOLEAN, EQUALS, NOTEQL, GREQ, LOEQ et PT_VIRG. 
- une expression régulière associée à ces tokens ont été ajoutées.

2. **parseur.y** :
- on utilise %start car maintenant le non-terminal principal n'est plus expression mais programme.
- on définit 9 tokens : NOMBRE, BOOLEAN, EQUALS, NOTEQL, GREQ, LOEQ, PT_VIRG FLOAT et IDENT. Notons que les opérations "==", "!=", "<=", ">=" sont des multisymboles d'où la création de leur token.
- on définit les règles d'associativité gauche grâce au %left.
- on définit les règles de priorités : L'affection '=' est définie en premier car elle est la moins prioritaire des opérations. Les opérations booléennes sont définies en deuxième. S'en suit du '+' et du '-' car ils sont moins prioritaires que le '*' et le '/' (que l'on a donc défini dans un troisième temps). Et pour finir, comme le '!' est prioritaire sur toutes les précédentes opérations, il a été défini en dernier.
- on définit une balise MOINSU pour sigifier qu'il a une autre priorité que le '-'.
- par conséquent, on a mis à jour la grammaire.


3. **test.txt**:

y=_f+2;  => error 

- une variable ne doit commencer que par une lettre minuscule

y=z=3;   => error 

- on ne peut pas avoir d'affectation à la suite

y=3=z=True; => error

x=3;(y=2;z=1;); => error 

- on ne peut pas mettre d'affectation dans des parenthèses

!et=oui; => error 

- on ne peut pas faire de négation d'une affectation

x_oui=(z=z;); => error 

2364agj=87; => error 

- soit il manque un point virgule entre le nombre et la variable soit la variable ne doit pas commencer par un nombre

x=3;  => ok

x=10.2;y=f_+2; => ok

s0hA_yla; => ok

i=0;i<10.5;i=i+0.5; => ok



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



