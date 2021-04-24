#include "TStack.h"


TStackPointer InitialiseStack()
{
    TStackPointer stack = (TStackPointer) malloc(sizeof(TStack));
    stack->count = 0;
    stack->top = NULL;

    return stack;
}

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

void* PopStack(TStackPointer stack)
{
    if(!IsEmptyStack(stack))
    {
        TNodePointer aux;
        aux = stack->top;
        void *info = aux->info;
        stack->top = stack->top->next;
        stack->count--;

        free(aux);
        aux = NULL;
        return info;
    }
    else
        return NULL;
    
}

void DisplayStack(TStackPointer stack, ShowInfoFunction showFunc, FILE *outputFILE)
{
    TNodePointer node = stack->top;
    DisplayList(node, showFunc, outputFILE);
}

void ClearStack(TStackPointer stack, FreeInfoFunction freeFunc)
{
    while(!IsEmptyStack(stack))
    {
        void *info = PopStack(stack);
        freeFunc(info);
    }
    free(stack);
    stack = NULL;
}

