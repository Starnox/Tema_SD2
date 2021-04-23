#include "TStack.h"


int PushStack(TStackPointer stack, void *info)
{
    TNodePointer aux;
    aux = InitialiseNode(info);
    if(aux == NULL)
    {
        printf("Eroare de memorie la alocarea nodului\n");
        return 0;
    }
    aux->next = stack->top;
    stack->top = aux;
    stack->count++;

    return 1;
}

int IsEmptyStack(TStackPointer stack)
{
    return (stack->top == NULL);
}

void* PopStack(TStackPointer stack, FreeInfoFunction freeFunc)
{
    if(!IsEmptyStack(stack))
    {
        TNodePointer aux;
        aux = stack->top;
        void *info = aux->info;
        stack->top = stack->top->next;
        stack->count--;
        DestroyNode(&aux,freeFunc);

        return info;
    }
    else
        return NULL;
    
}

void ClearStack(TStackPointer stack, FreeInfoFunction freeFunc)
{
    while(!IsEmptyStack(stack))
    {
        PopStack(stack, freeFunc);
    }
}

