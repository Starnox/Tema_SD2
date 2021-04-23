#include "TLista.h"

typedef struct stack
{
    int count;
    TNodePointer top;
}TStack, *TStackPointer;


int PushStack(TStackPointer stack, void *info);
int IsEmptyStack(TStackPointer stack);
void* PopStack(TStackPointer stack, FreeInfoFunction freeFunc);
void ClearStack(TStackPointer stack, FreeInfoFunction freeFunc);