# Tema 2 SD
## Elev: Mihailescu Eduard-Florin
## Grupa: 312CB

### Descriere generala
Acest cod are ca scop rezolvarea temei 2 propusa in cadrul cursului de Structuri de date(SD)
din anul I, seria CB de la Facultatea de Automatica si Calculatoare. Comentarile pentru
cod sunt scrise in limba engleza in vederea antrenarii acestui skill si pentru o potentiala
incarcare pe github la finalul anului. Specific faptul ca tema a obtinut un punctaj maxim
la rularea locala (135/135 si 20/20);

### Structura
Codul este impartit in 7 fisiere sursa (.c) si 7 fisiere header (.h) aferente.
Astfel in:
*   `TLista.c` - se regaseste implementarea listelor simplu inlantuite generice
    -   Initializare -> `InitialiseNode()`
    -   Gasire -> `FindElement()`
    -   Afisare -> `DisplayList()`
    -   Inlaturare -> `RemoveFromList()`
    -   Distrugere a memoriei -> `DestroyNode()`, `DestroyList()` 
    -   Inserare -> `InsertEnd()` 
    -   Insereare ordonata -> `OrderedInsert()`

*   `TQueue.c` - implementarea structurii de 'coada' ce se foloseste de listele enuntate anterior
    -   Initializare -> `InitialiseQueue()`
    -   Verificare coada goala -> `IsEmptyQueue()`
    -   Extragere element din varful cozii fara eliminare -> `QueueTop()`
    -   Inserare in coada -> `QueuePush()`
    -   Afisare Coada -> `DisplayQueue()`
    -   Extragere element din varful cozii cu eliminare -> `QueuePop()`
    -   Eliminare din coada element dat -> `RemoveFromQueueList()`
    -   Distrugere coada -> `ClearQueue()`

*   `TStack.c` - implementarea structurii de 'stiva' ce se foloseste de listele enuntate anterior
    -   Initializare -> `InitialiseStack()`
    -   Verificare stiva goala -> `IsEmptyStack()`
    -   Inserare in stiva -> `PushStack()`
    -   Afisare stiva -> `DisplayStack()`
    -   Extragere element din varful stivii cu eliminare -> `PopStack()`
    -   Eliminare din stiva element dat -> `RemoveFromStackList()`
    -   Distrugere stiva -> `ClearStack()`
    -   Cautare element in stiva -> `FindElementInStack()`

*   `TSeries.c` - implementarea unei structuri 'serial'
    -   Initializare -> `InitialiseSeries()`
    -   Adaugare sezon -> `AddSeason()`
    -   Afisares serial -> `DisplaySeries()`
    -   Distrugere serial -> `FreeSeries()`

*   `TSeason.c` - implementarea unei structuri 'sezon'
    -   Initializare -> `InitialiseSeason()`
    -   Adaugare episod -> `AddEpisode()`
    -   Distrugere sezon -> `FreeSeason()`

*   `TEpisode.c` - implementarea unei structuri 'episod'
    -   Initializare -> `InitialiseEpisode()`
    
*   `tema2.c` - definitia functiei main, citirea datelor de intrare, prelucrarea lor
cu ajutorul structurilor precizate anteriror si afisarea rezultatelor intr-un fisier
de iesire



