/* MIHAILESCU Eduard-Florin - 312CB */
#include "TSeries.h"
#include "TQueue.h"
#include "TStack.h"
#include "TLista.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int CompareSeries(void * seriesA, void *seriesB);
TSeriesPointer ReadSeries(FILE *inputFile); // (0/1) succes or failure
TSeasonPointer ReadSeason(FILE *inputFile);
int MyFindFunction(void *a, void *b);
int FindFunctionForTwoNodes(void *a, void *b);
int CompareSeriesFromTop(void *seriesA, void *seriesB);
void ReadjustOrder(TNodePointer node);

// returns 1 if we watched the whole series, 0 otherwise
int WatchSeries(TSeriesPointer series, int duration, FILE *outputFile);

TSeriesPointer VerifyIntegrity(TNodePointer node);

void Add(FILE *inputFile, FILE *outputFile, TNodePointer *tendinte, 
        TNodePointer *documentare, TNodePointer *tutoriale, TNodePointer *all);


void Show(FILE *inputFile, FILE *outputFile, TNodePointer *tendinte, 
        TNodePointer *documentare, TNodePointer *tutoriale, TNodePointer *top10,
        TQueuePointer *watch_later, TStackPointer *currently_watching,
        TStackPointer *history);

void Add_Sez(FILE *inputFile, FILE *outputFile, TNodePointer all);

void Later(FILE *inputFile, FILE *outputFile, TNodePointer *tendinte, 
        TNodePointer *documentare, TNodePointer *tutoriale, TNodePointer *top10,
        TNodePointer all, TQueuePointer watch_later);

void Watch(FILE *inputFile, FILE *outputFile, TNodePointer *tendinte, 
        TNodePointer *documentare, TNodePointer *tutoriale, TNodePointer *top10,
        TNodePointer all, TQueuePointer *watch_later,
        TStackPointer *currently_watching, TStackPointer *history);

void Add_Top(FILE *inputFile, FILE *outputFile, TNodePointer *all,
            TNodePointer *residuu, TNodePointer *top10);