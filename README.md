# Informatica e Computazione 2022-2023

# Interprete per Linguaggio LISP-like

## Notazione di base

Data una grammatica libera dal contestoG= (VN,VT,P,S)
+ la produzioneA→α|β abbrevia le produzioni
  - A→α
  - A→β
+ i caratteri corsivi definiscono i simboli non terminali VN, ad esempio *program,statement*, ecc.
+ i caratteri standard sono riservati ai simboli terminali VT, ad esempio SET, MUL, (, ), ecc.
+ Come consueto, il simbolo *epsilon* denota la stringa vuota.

## Grammatica di input

```
program → stmt_block
stmt_block→statement | ( BLOCKstatement_list)
statement_list → statement statement_list | statement

statement → variable_def | io_stmt | cond_stmt | loop_stmt

variable_def → ( SETvariable_id num_expr)
io_stmt → ( PRINTnum_expr) | ( INPUTvariable_id)
cond_stmt → ( IFbool_expr stmt_block stmt_block)
loop_stmt → ( WHILEbool_expr stmt_block)

num_expr → ( ADDnum_expr num_expr) | ( SUBnum_expr num_expr) | ( MULnum_expr num_expr) | ( DIVnum_expr num_expr) | number | variable_id

bool_expr → (LTnum_expr num_expr) | (GTnum_expr num_expr) | (EQnum_expr num_expr) | (ANDbool_expr bool_expr) | (ORbool_expr bool_expr) | (NOTbool_expr) | TRUE | FALSE

variable_id → alpha_list
alpha_list → alpha alpha_list | alpha
alpha → a | b | c | ... | z | A | B | C | ... | Z

number → -posnumber | posnumber
posnumber → 0 | sigdigit rest
sigdigit → 1 |...| 9
rest → digit rest| epsilon
digit → 0 |sigdigit
```

+ La grammatica proposta è non ambigua
+ Al più due simboli non terminali disambiguano qualsiasi produzione:
- “(SET”, “(PRINT”, “(INPUT”, ecc. consentono di risolvere l’ambiguità tra le varie istruzioni
- “(ADD”, “(SUB”, ecc., consentono di risolvere l’ambiguità tra i vari tipi di espressione


## Esempio di file di input: calcolo del fattoriale
```
(BLOCK
  (INPUT n)
  (SET result 1)
  (WHILE (GT n 0)
    (BLOCK
      (SET result (MUL result n))
      (SET n (SUB n 1))
    )
  )
(PRINT result))
```
+ Spazi, tabulazioni e righe vuote non fanno parte della sintassi del programma
+ Devono essere considerati come “spazio vuoto” e ignorati.
+ Le **parole chiave** in questo programma sono BLOCK, INPUT, SET, WHILE, GT, MUL, SUB e PRINT

## Interpretazione delle dichiarazioni di variabili
Il risultato corrispondente ad una istruzione
```
(SETvariable_id num_expr)
```
+ deve essere:
  - la **creazione** della variablevariable_id, se non era stata già definita in precedenza, e
  - l’ **assegnazione** alla variablevariable_iddel valore dell’espressione num_expr.
+ Possono verificarsi i seguenti errori:
  - la dichiarazione non è sintatticamente corretta
  - *variable_id* è una parola chiave
  - *num_exprnon* è sintatticamente corretta, oppure contiene un errore semantico (ad e.s., divisione per zero).

## Interpretazione dello statement di input

Il risultato corrispondente ad una istruzione
```
(INPUTvariable_id)
```
+ deve essere:
  - la **creazione** della variablevariable_id, se non era stata già definita in precedenza, e
  - l’ **assegnazione** alla variablevariable_iddel valore **letto da console**.
+ Possono verificarsi i seguenti errori:
  - l’istruzione non è sintatticamente corretta
  - variable_idè una parola chiave
  - viene inserito da console un valore illecito (sono consentiti solo numeri interi positivi e negativi).

## Interpretazione dello statement di output
Il risultato corrispondente ad una istruzione
```
(PRINTnum_expr)
```
+ deve essere la **visualizzazione in console del valore** dell’espressione *num_expr*.
+ Possono verificarsi i seguenti errori:
  - l’istruzione non è sintatticamente corretta,
  - *num_exprnon* è sintatticamente corretta, oppure contiene variabili non definite in precedenza con SET o INPUT, oppure contiene un errore semantico (ad e.s., divisione per zero).

## Interpretazione dell’istruzione di scelta condizionata

Il risultato corrispondente ad una istruzione
```
(IFbool_expr stmt_block 1 stmt_block 2 )
```
+ deve essere:
  - l’esecuzione distmt_block 1 nel caso in cuibool_exprvaluti a vero, oppure
  - l’esecuzione distmt_block 2 nel caso in cuibool_exprvaluti a falso.
+ Possono verificarsi i seguenti errori:
  - la dichiarazione non è sintatticamente corretta,
  - *bool_exprnon* è sintatticamente corretta o contiene variabili non definite in precedenza, oppure
  - uno dei due *stmt_block* non è sintatticamente corretto, oppure, se eseguito, contiene un errore semantico (ad e.s., divisione per zero).

## Interpretazione dell’istruzione di iterazione

Il risultato corrispondente ad una istruzione
```
(WHILEbool_expr stmt_block)
```
deve essere l’esecuzione distmt_blockfintanto che l’espressionebool_expr valuta a vero; l’esecuzione non avviene sebool_exprè falsa in partenza.

Possono verificarsi i seguenti errori:
- la dichiarazione non è sintatticamente corretta,
- *bool_exprnon* è sintatticamente corretta o contiene variabili non definite in precedenza, oppure
- lo *stmt_blocknon* è sintatticamente corretto, oppure, se eseguito, contiene un errore semantico (ad e.s., divisione per zero).

## Interpretazione di un blocco di istruzioni

Il risultato corrispondente ad una istruzione
```
(BLOCKstatement 1.. .statementn)
```
deve essere l’esecuzione in sequenza dei diversi statement.

Possono verificarsi i seguenti errori:
- la dichiarazione non è sintatticamente corretta,
- per qual che i, **statment** non è sintatticamente corretto, contiene variabili non definite in precedenza, oppure contiene un errore semantico (ad e.s., divisione per zero).

## Interpretazione di espressioni

+ Le espressioni numeriche vengono interpretate con l’ovvia semantica per valori ed operatori: somma per ADD, sottrazione per SUB, ecc.
+ Nelle espressioni booleane, gli operatori relazionali hanno la seguente semantica:
  - GT sta per “greater than”, quindi (GTa b) è vero se il valore di a è strettamente maggiore di quello di b;
  - Analogamente LT sta per “lesser than”
  - EQ sta per “equal” con il relativo significato inteso.
+ Gli operatori booleani AND, OR, NOT hanno anch’essi l’ovvia semantica; AND e OR sono cortocircuitati , ossia
  - (a AND b) nel caso in cuiavaluti a falso è immediatamente valutata a falso (bnon viene valutato);
  - (a OR b) nel caso in cuiavaluti a vero è immediatamente valutata a vero (bnon viene valutato).

## Osservazioni aggiuntive
+ La grammatica **non permette** la definizione di variabili che non siano di tipo numerico: SET richiede unanum_expr.
+ Nel caso di INPUT viene imposto il vincolo che il valore letto sia un intero.
+ Esiste un unico ambito globale per le variabili.
+ Le variabili sono definite dinamicamente (non è necessario dichiararle prima di utilizzarle per la prima volta come in C/C++/Java).

## Esempio di esecuzione

Ad esempio, in corrispondenza del programma visto prima, l’interazione con l’utente sarebbe il seguente:
```
> 5
120
```
**Nota** : Come ulteriore semplificazione, si assuma che gli interi forniti in ingresso siano sempre rappresentabili in registri a 64 bit (gliint64_t del C++), ossia per qualsiasi numeronutilizzato si ha che  -26^3 ≤ n < 26^3.
**Nota** : Non è necessario gestire condizioni di overflow o underflow nelle operazioni aritmetiche, mentre è necessario gestire la divisione per zero.

## Analisi lessicale

+ Lettura del sorgente fornendo in uscita la sequenza degli **elementi lessicali ( parole** o token) del programma.
+ Formalmente, per la grammatica dei file sorgente, un elemento lessicale corrisponde ad uno dei seguenti **gruppi** :
  + una parola chiave : BLOCK, INPUT, PRINT, SET, WHILE, IF, GT, LT, EQ, AND, OR, NOT, TRUE, FALSE, ADD, SUB, MUL, DIV;
  + una parentesi aperta o chiusa;
  + un numero (definito con le regolenumber);
  + un variabile (definita con le regolevariable_id);
+ I token corrispondono ai simboli terminali di una versione “astratta” della grammatica che descrive le espressioni.

## Grammatica astratta

L’utilizzo dei token corrisponde a utilizzare per l’analisi sintattica le seguenti regole (in grassetto i simboli terminali):

>> *program* → *stmt_block*
>> 
>> *stmt_block* → *statement* | **( BLOCK** *statement_list* **)**
>>
>> *statement_list* → *statement statement_list* | *statement*
>
>> *statement* → *variable_def* | *io_stmt* | *cond_stmt* | *loop_stmt*
>
>> *variable_def* → **( SET** *variable_id num_expr* **)**
>> *io_stmt* → **( PRINT** *num_expr* **)** | **( INPUT** *variable_id* **)**
>> *cond_stmt* → **( IF** *bool_expr stmt_block stmt_block* **)**
>> *loop_stmt* → **( WHILE** *bool_expr stmt_block* **)**
>
>> *num_expr* → **( ADD** *num_expr num_expr* **)** | **( SUB** *num_expr num_expr* **)** | **( MUL** *num_expr num_expr* **)** | **( DIV** *num_expr num_expr* **)** | *number* | *variable_id*
>
>> *bool_expr* → **(LT** *num_expr num_expr* **)** | **(GT** *num_expr num_expr* **)** | **(EQ** *num_expr num_expr* **)** | **(AND** *bool_expr bool_expr* **)** | **(OR** *bool_expr bool_expr* **)** | **(NOT** *bool_expr* **)** | **TRUE** | **FALSE**

## Analisi sintattica
+ Legge la sequenza di token fornita dall’analizzatore lessicale e ne controlla la correttezza sintattica.
+ Fornisce in uscita una descrizione sotto forma di albero del programma in ingresso (c.d. albero sintattico )

## Analisi semantica
+ Prende in input l’albero sintattico
+ Crea una tabella dei simboli per memorizzare le variabili e i valori ad esse associati
+ Crea degli opportuni registri per la valutazione delle espressioni numeriche e booleane (Suggerimento: considerare un’architettura a stack)
+ Valuta l’albero sintattico (interpreta il programma) utilizzando una visita.
+ Per eseguire la visita si può utilizzare un oggetto “Visitor” con opportuni metodi che consentano l’analisi dei vari elementi degli oggetti “Interpreter”.

## Specifiche di input/output
+ L’interprete prende in input **un parametro da linea di comando** che corrisponde al nome (completo di percorso) del file contenente il programma da interpretare
+ Il programma richiede eventuali input e presenta eventuali output in console

## Specifiche di consegna
+ Standard C++17
+ Evitare estensioni specifiche di una IDE o di un sistema operativo
+ Consegna dei sorgenti (header.he file.cpp) e del diagramma UML dell’applicazione su Aulaweb (singolo file.zip)
+ Il file.cppcontenente ilmaindeve chiamarsi lispInterpreter
+ Utilizzare le guardie di inclusione invece delle direttivepragma; ad esempio, il fileHeader.h va strutturato come:
```
#ifndef HEADER_H
#define HEADER_H

<corpo del file Header.h>

#endif
```

## Valutazione
+ Il progetto fornisce un punteggio massimo di 10 punti così ripartiti:
  + I Correttezza sintattica 4/10: il programma compila senza errori, prende in input il file da linea di comando, genera output su console, non va in loop o in crash
  + I Correttezza su test 4/10: il programma esegue correttamente i test forniti (2/10) e una serie di test ulteriori predisposti in fase di correzione (2/10)
  + I Struttura e documentazione 2/10: il diagramma UML è aderente all’implementazione, il codice sorgente è organizzato e commentato chiaramente
+ Il progetto è individuale : l’eccessiva similitudine tra diversi progetti darà luogo a penalizzazioni sul punteggio finale.
