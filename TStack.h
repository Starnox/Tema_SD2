#include "TLista.h"

#ifndef TSTACK_H
#define TSTACK_h
typedef struct stack
{
    int count;
    TNodePointer top;
}TStack, *TStackPointer;


TStackPointer InitialiseStack();
int PushStack(TStackPointer stack, void *info);
int IsEmptyStack(TStackPointer stack);
void* PopStack(TStackPointer stack);
void ClearStack(TStackPointer stack, FreeInfoFunction freeFunc);

#endif