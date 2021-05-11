# Fragment c1.3

Réalisé par : Hajar BOUZIANE

## Description 

1. **lexeur.l** : 
- le fichier *parseur.tab.h* est inclu car il permet de définir les tokens NAN, NUMBER, IDENT, BOOLEAN, EQUALS, NOTEQL, GREQ, LOEQ, INCRE et PT_VIRG. 
- une expression régulière associée à ces tokens ont été ajoutées.
- une expression régulière a été créé pour des commentaires unilignes.
- une autre expression régulière a été créé pour des commentaires multilignes.


2. **parseur.y** :
- on utilise %start car maintenant le non-terminal principal n'est plus expression mais programme.
- on définit 10 tokens : NAN, NUMBER, IDENT, BOOLEAN, EQUALS, NOTEQL, GREQ, LOEQ, INCRE et PT_VIRG. Notons que les opérations "==", "!=", "<=", ">=" et "++" sont des multisymboles d'où la création de leur token.
- on définit les règles d'associativité gauche grâce au %left.
- on définit les règles de priorités : L'affection '=' est définie en premier car elle est moins prioritaire que toutes les autres opérations. Les opérations booléennes sont définies en deuxième. S'en suit du '+' et du '-' car ils sont moins prioritaires que le '*' et le '/' (que l'on a donc défini dans un troisième temps). Comme le '++' est prioritaire sur toutes les précédentes opérations, il a été défini après le '!'.
- on définit une balise MOINSU pour sigifier qu'il a une autre priorité que la soustraction '-'.
- par conséquent, on a mis à jour la grammaire.


3. **test.txt**:

3;

56e-89;

.364;

.364e5;

.364e-5;

23.568;

346.78e53;

346.78e-53;

3/0;

0/0;

0./0;

0/0.;

0/.0;

.0/0;

/* 

 ** je suis un commentaire **

 ++ je suis un commentaire **

 // je suis un commentaire ++

 ** je suis un commentaire 00

 ** je suis un commentaire **

 *****/

 6+m; // je suis un autre commentaire mais uniligne

 8+0;dksnvo=h;y++;
 
***

lex::NUMBER 3

lex::PT_VIRG ;

lex::NUMBER 56e-89

lex::PT_VIRG ;

lex::NUMBER .364

lex::PT_VIRG ;

lex::NUMBER .364e5

lex::PT_VIRG ;

lex::NUMBER .364e-5

lex::PT_VIRG ;

lex::NUMBER 23.568

lex::PT_VIRG ;

lex::NUMBER 346.78e53

lex::PT_VIRG ;

lex::NUMBER 346.78e-53

lex::PT_VIRG ;

lex::NAN 3/0

lex::PT_VIRG ;

lex::NAN 0/0

lex::PT_VIRG ;

lex::NAN 0./0

lex::PT_VIRG ;

lex::NAN 0/0.

lex::PT_VIRG ;

lex::NAN 0/.0

lex::PT_VIRG ;

lex::NAN .0/0

lex::PT_VIRG ;

lex::NUMBER 6

lex::char +

lex::IDENT m

lex::PT_VIRG ;

lex::NUMBER 8

lex::char +

lex::NUMBER 0

lex::PT_VIRG ;

lex::IDENT dksnvo

lex::char =

lex::IDENT h

lex::PT_VIRG ;

lex::IDENT y

lex::INCRE ++

lex::PT_VIRG ;


Parsing:: syntax OK


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



