# Fragment p0.2

Réalisé par : BOUZIANE Hajar

## Description 

1. **lexeur.l** : 
- le fichier *parseur.tab.h* est inclu car il permet de définir les token NOMBRE, BOOLEAN, EQUALS, NOTEQL, GREQ, LOEQ, PT_VIRG et FLOAT. 
- une expression régulière associée à ce token a été ajoutée.

2. **parseur.y** :
- on définit 8 tokens : NOMBRE, BOOLEAN, EQUALS, NOTEQL, GREQ, LOEQ, PT_VIRG et FLOAT. Notons que les opérations "==", "!=", "<=", ">=" sont des multisymboles d'où la création de leur token.
- on définit les règles d'associativité gauche grâce au %left.
- on définit les règles de priorités : les opérations booléennes (étant les moins prioritaires) sont définies en premier. S'en suit du '+' et du '-' car elles sont moins prioritaires que le '*' et le '/' (que l'on a donc défini dans un troisième temps). Et pour finir, comme le '!' est prioritaire sur toutes les précédentes opérations, il a été défini en dernier.
- on définit une balise MOINSU pour sigifier qu'il a une autre priorité que le '-'.
- par conséquent, on a mis à jour la grammaire sans oublier d'ajouter les opérations '<' et '>'.


3. **test.txt**:

1+2==3;
- AddiNb
- Equals 

=> ok

(1+2)==3;
- AddiNb
- Equals 

=> ok

1+(2==3); 
- Equals
- AddiNb 

=> ok

True+3!=5.123; 
- AddiNb
- NotEq 

=>ok

Fale<=33333/33; 
- DiviNb
- LoEq 

=> ok

0-32<(7+7.000000);
- SubiNb
- AddiNb
- Lo 

=> ok

True*(3>=43); 
- GrEq
- MultNb 

=> ok

True*(3>43);
- Gr
- MultNb

=>ok

!!True; 
- Not
- Not 

=> ok

True*34+1==False-!True; 
- MultNb
- AddiNB
- Not
- SubiNb
- Equals 

=> ok

!(True==False); 
- Equals
- Not 

=> ok

True==!False;
- Not
- Equals 

=> ok

!!True<=-3.6!=21+4; 
- Not
- Not
- Moinsu
- LoEq
- AddiNb
- NoEq 

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



