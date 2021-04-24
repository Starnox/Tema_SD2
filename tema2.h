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