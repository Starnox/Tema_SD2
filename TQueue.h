#include "TLista.h"

#ifndef TQUEUE_H
#define TQUEUE_H
typedef struct queue
{
    int count;
    TNodePointer front;
    TNodePointer back;
}TQueue, *TQueuePointer;

TQueuePointer InitialiseQueue(); // initialise an empty queue
int IsEmptyQueue(TQueuePointer queue); // check if empty
int QueuePush(TQueuePointer queue, void *info); // 1 for succes 0 for failure
void* QueuePop(TQueuePointer queue);
void ClearQueue(TQueuePointer queue, FreeInfoFunction freeFunc);
void DisplayQueue(TQueuePointer queue, ShowInfoFunction showFunc, FILE *outputFILE);


#endif