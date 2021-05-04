/* MIHAILESCU Eduard-Florin - 312CB */
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

void ReverseStack(TStackPointer *stack)
{
    TStackPointer stackCopy = InitialiseStack();
    while(!IsEmptyStack(*stack))
    {
        void *currentInfo = PopStack(*stack);
        PushStack(stackCopy, currentInfo);
    }
    free(*stack);
    *stack = stackCopy;
}

void RemoveFromStackList(TStackPointer *stack, void *info, FindFunction findFunction)
{
    TStackPointer stackCopy = InitialiseStack();

    while(!IsEmptyStack(*stack))
    {
        void *currentInfo = PopStack(*stack);
        if(findFunction(currentInfo, info) != 1)
            PushStack(stackCopy, currentInfo);
    }
    free(*stack);
    ReverseStack(&stackCopy);
    *stack = stackCopy;
}

int IsEmptyStack(TStackPointer stack)
{
    if(stack == NULL)
        return 1;
    return (stack->top == NULL);
}

void* FindElementInStack(TStackPointer *stack, void *info,
                                 FindFunction findFunction)
{
    TStackPointer stackCopy = InitialiseStack();
    void *res = NULL;

    while(!IsEmptyStack(*stack))
    {
        void *currentInfo = PopStack(*stack);
        if(findFunction(currentInfo, info) == 1)
            res = currentInfo;
        PushStack(stackCopy, currentInfo);
    }
    free(*stack);
    ReverseStack(&stackCopy);
    *stack = stackCopy;
    return res;
}

void* PopStack(TStackPointer stack)
{
    if(stack == NULL)
        return NULL;
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

void DisplayStack(TStackPointer *stack, ShowInfoFunction showFunc, FILE *outputFILE)
{
    TStackPointer stackCopy = InitialiseStack();

    fprintf(outputFILE,"[");
    while(!IsEmptyStack(*stack))
    {
        void *currentInfo = PopStack(*stack);
        showFunc(outputFILE, currentInfo);
        if(!IsEmptyStack(*stack))
           fprintf(outputFILE,", ");
        
        PushStack(stackCopy, currentInfo);
    }
    fprintf(outputFILE,"].\n");
    free(*stack);
    ReverseStack(&stackCopy);
    *stack = stackCopy;
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

