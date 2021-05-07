# Frangment 0.2

Réalisé par : BOUZIANE Hajar

## Exemple et trace d'exécution

### Test sur des expressions à syntaxe invalide:
True<=false; = > error

Trueaba; => error

True<=3; => error

### Test sur des expressions à syntaxe valide:

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

