#include "TQueue.h"

TQueuePointer InitialiseQueue()
{
    TQueuePointer queue = (TQueuePointer) malloc(sizeof(TQueue));
    queue->count = 0;
    queue->front = NULL;
    queue->back = NULL;

    return queue;
}

int IsEmptyQueue(TQueuePointer queue)
{
    if(queue == NULL)
        return 1;
    return (queue->front == NULL);
}

void* QueueTop(TQueuePointer queue)
{
    if(queue != NULL)
    {
        return queue->front->info;
    }
    return NULL;
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


void DisplayQueue(TQueuePointer queue, ShowInfoFunction showFunc, FILE *outputFILE)
{
    TNodePointer node = queue->front;
    DisplayList(node, showFunc, outputFILE);
}

// just returns the info, the memory needs to be free manually
void* QueuePop(TQueuePointer queue)
{
    if(queue == NULL)
        return NULL;
    if(!IsEmptyQueue(queue))
    {
        void *info = queue->front->info;
        TNodePointer aux = queue->front;
        queue->front = queue->front->next;
        queue->count--;
        if(queue->count < 0)
            queue->count = 0;

        if(queue->front == NULL) // if the queue is empty
        {
            queue->back = NULL;
        }
        free(aux);
        aux = NULL;
        return info;
    }
    return NULL;
}

void RemoveFromQueueList(TQueuePointer queue, void *info, FindFunction findFunction)
{
    int status = RemoveFromList(&(queue->front), info, findFunction);
    if(status == 1)
    {
        queue->count--;
        if(queue->count <= 0)
        {
            queue->count = 0;
            queue->front = NULL;
            queue->back = NULL;
        }
        else
        {
            // reput queue->back in the correct position
            TNodePointer aux = queue->front;
            while(aux->next != NULL)
            {
                aux = aux->next;
            }
            queue->back = aux;
        }
    }
}

void ClearQueue(TQueuePointer queue, FreeInfoFunction freeFunc)
{
    while(!IsEmptyQueue(queue))
    {
        void *info = QueuePop(queue);
        freeFunc(info);
    }
    free(queue);
    queue = NULL;
}
