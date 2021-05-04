/* MIHAILESCU Eduard-Florin - 312CB */
#include "TQueue.h"
#include "TSeason.h"
#include "string.h"

#define DIM_MAX 100

#ifndef TSERIES_H
#define TSERIES_H
typedef struct Series
{
    int id;
    char *name;
    double rating;
    int nrSeasons;
    int nrOrder; // -1 if not in top 10 else the ranking
    TQueuePointer seasons;
}TSeries, *TSeriesPointer;

void FreeSeries(void *info);
TSeriesPointer InitialiseSeries(int id, char *name, double rating, int nrSeasons);
int AddSeason(TSeriesPointer series,  TSeasonPointer season);
void DisplaySeries(FILE *outputFILE ,void *series);

#endif