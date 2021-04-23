#include "TSeason.h"

void FreeSeason(void* info)
{
    TSeasonPointer  seasonInfo = (TSeasonPointer) info;
    ClearQueue(seasonInfo->episodes, free);
}

TSeasonPointer InitialiseSeason(int numberOfEpisodes)
{
    TSeasonPointer season = (TSeasonPointer) malloc(sizeof(TSeason));
    if(season == NULL)
    {
        printf("NU s-a putut aloca sezonul\n");
        return NULL;
    }

    season->numberOfEpisodes = numberOfEpisodes;
    InitialiseQueue(season->episodes);

    return season;
}

int AddEpisode(TSeasonPointer season, TEpisodePointer episode)
{
    int result = QueuePush(season->episodes,(void *) episode);
    if(result == 0)
    {
        printf("Episodul nu a putut fi adaugat");
        return 0;
    }
    return 1;
}