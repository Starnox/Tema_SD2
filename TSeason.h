/* MIHAILESCU Eduard-Florin - 312CB */
#include "TQueue.h"
#include "TEpisode.h"

#ifndef TSEASON_H
#define TSEASON_H

typedef struct season
{
    int numberOfEpisodes;
    TQueuePointer episodes;
}TSeason, *TSeasonPointer;

int AddEpisode(TSeasonPointer season, TEpisodePointer episode);
TSeasonPointer InitialiseSeason(int numberOfEpisodes);
void FreeSeason(void* info);

#endif