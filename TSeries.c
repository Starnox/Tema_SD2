#include "TSeries.h"

void FreeSeries(void *info)
{
    TSeriesPointer infoSeries = (TSeriesPointer) info;
    free(infoSeries->name);
    infoSeries->name = NULL;
    ClearQueue(infoSeries->nrSeasons, FreeSeason);
}

int AddSeason(TSeriesPointer series,  TSeasonPointer season)
{
    int result = QueuePush(series->seasons,(void *) season);
    if(result == 0)
    {
        printf("Sezonul nu a putut fi adaugat");
        return 0;
    }
    return 1;
}

TSeriesPointer InitialiseSeries(int id, char *name, double rating, int nrSeasons)
{
    TSeriesPointer newSeries = (TSeriesPointer) malloc(sizeof(TSeries));
    if(newSeries == NULL)
    {
        printf("Nu a putut fi initializat un serial nou");
        return NULL;
    }

    // set the parameters
    newSeries->id = id;
    newSeries->name = (char *) malloc(sizeof(char) * DIM_MAX);
    strcpy(newSeries->name, name);
    newSeries->rating = rating;
    newSeries->nrSeasons = nrSeasons;

    InitialiseQueue(newSeries->seasons); // initialise the queue

    return newSeries;
}

char* DisplaySeries(TSeriesPointer series)
{
    char *result = (char) malloc(sizeof(char) * DIM_MAX);
    sprintf(result,"(<%s>, <%lf>)", series->name, series->rating);

    return result; // TODO free the memory
}