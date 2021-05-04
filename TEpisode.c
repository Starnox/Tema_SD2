/* MIHAILESCU Eduard-Florin - 312CB */
#include "TEpisode.h"

TEpisodePointer InitialiseEpisode(int duration)
{
    TEpisodePointer newEpisode = (TEpisodePointer) malloc(sizeof(TEpisode));
    newEpisode->duration = duration;
    return newEpisode;
}