
# Prova Finale di Algoritmi e Principi dell'Informatica - A.A. 2022-2023

Progetto finale per il corso di Algoritmi e Principi dell'Informatica dell'anno accademico 2022-2023.

**Docente:** Davide Martineghi

**Valutazione:** 30 e lode

# Progetto Finale - Algoritmi e Strutture Dati A.A. 2022-2023

## Obiettivi del Progetto

1. **Gestione Stazioni di Servizio**
   - Aggiungere stazioni di servizio lungo l'autostrada, ognuna con un parco veicoli caratterizzato da diverse autonomie.
   - Rimuovere stazioni e gestire l’aggiunta o rimozione di veicoli da ciascuna stazione.

2. **Pianificazione del Percorso Ottimale**
   - Calcolare il percorso con il **minor numero di tappe** tra due stazioni, tenendo conto dell'autonomia dei veicoli.
   - In caso di percorsi equivalenti, preferire quello con le stazioni più vicine all’inizio dell’autostrada.

3. **Rispetto dei Vincoli**
   - Ogni tappa deve rispettare l'autonomia dei veicoli, con il conducente che noleggia un nuovo veicolo ad ogni fermata, senza possibilità di tornare indietro.

4. **Risposte ai Comandi**
   - Rispondere ai comandi di aggiunta/rimozione di stazioni e veicoli, e pianificare il percorso ottimale, restituendo la sequenza di tappe o "nessun percorso" se non esiste una soluzione valida.

Il programma non solo deve restituire risultati corretti, ma deve rispettare rigorosi vincoli in termini di utilizzo di memoria e tempo di esecuzione, come illustrato nella tabella seguente:

| Valutazione | Memoria | Tempo  | Esito |
|-------------|---------|--------|-------|
| 18          | 128 MiB | 19 s   | ✅    |
| 21          | 118 MiB | 15 s   | ✅    |
| 24          | 108 MiB | 10 s   | ✅    |
| 27          | 98 MiB  | 6 s    | ✅    |
| 30          | 88 MiB  | 4 s    | ✅    |
| 30L         | 78 MiB  | 1 s    | ✅    |
