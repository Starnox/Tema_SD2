#include "TQueue.h"
#include "TStack.h"
#include "TSeason.h"

#define DIM_MAX 100

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
char* CreateDisplayString(TSeriesPointer series);