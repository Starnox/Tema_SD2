build: 
	gcc -Wall -g -o tema2 tema2.c TLista.c TQueue.c TStack.c TSeries.c TSeason.c TEpisode.c
clean:
	rm -rf tema2