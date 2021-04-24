#include <stdio.h>
#include <stdlib.h>


#ifndef TEPISODE_H
#define TEPISODE_h
typedef struct episode
{
    int duration;
}TEpisode, *TEpisodePointer;

TEpisodePointer InitialiseEpisode(int duration);

#endif