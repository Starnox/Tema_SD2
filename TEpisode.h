#include <stdio.h>
#include <stdlib.h>

typedef struct episode
{
    int duration;
}TEpisode, *TEpisodePointer;

TEpisodePointer InitialiseEpisode(int duration);