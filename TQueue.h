#include "TLista.h"


typedef struct queue
{
    int count;
    TNodePointer front;
    TNodePointer back;
}TQueue, *TQueuePointer;

void InitialiseQueue(TQueuePointer queue); // initialise an empty queue
int IsEmptyQueue(TQueuePointer queue); // check if empty
int QueuePush(TQueuePointer queue, void *info); // 1 for succes 0 for failure
void* QueuePop(TQueuePointer queue, FreeInfoFunction freeFunc);
void ClearQueue(TQueuePointer queue, FreeInfoFunction freeFunc);
