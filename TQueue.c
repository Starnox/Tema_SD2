#include "TQueue.h"

void InitialiseQueue(TQueuePointer queue)
{
    queue->count = 0;
    queue->front = NULL;
    queue->back = NULL;
}

int IsEmptyQueue(TQueuePointer queue)
{
    return (queue->back == NULL);
}

int QueuePush(TQueuePointer queue, void *info)
{
    TNodePointer node = InitialiseNode(info);
    if(node == NULL)
    {
        printf("Eroare de memorie la alocarea nodului\n");
        return 0;
    }

    if(!IsEmptyQueue(queue))
    {
        // Add to the end of the queue
        queue->back->next = node;
        queue->back = node;
    }
    else
    {
        queue->front = node;
        queue->back = node;
    }
    queue->count++;

    return 1;
}

void* QueuePop(TQueuePointer queue, FreeInfoFunction freeFunc)
{
    if(!IsEmptyQueue(queue))
    {
        TNodePointer aux;
        void *info = queue->front->info;
        aux = queue->front;
        queue->front = queue->front->next;
        queue->count--;
        DestroyNode(&aux, freeFunc);
        return info;
    }
    return NULL;
}

void ClearQueue(TQueuePointer queue, FreeInfoFunction freeFunc)
{
    while(!IsEmptyQueue(queue))
    {
        QueuePop(queue, freeFunc);
    }
}
