#include "TQueue.h"
#include "TEpisode.h"

typedef struct season
{
    int numberOfEpisodes;
    TQueuePointer episodes;
}TSeason, *TSeasonPointer;

int AddEpisode(TSeasonPointer season, TEpisodePointer episode);
TSeasonPointer InitialiseSeason(int numberOfEpisodes);
void FreeSeason(void* info);