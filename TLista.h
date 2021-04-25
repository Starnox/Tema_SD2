#include <stdio.h>
#include <stdlib.h>


#ifndef TLISTA_H
#define TLISTA_H
typedef struct node
{
    void *info;
    struct node *next;
} TNode, *TNodePointer;


typedef void (*FreeInfoFunction) (void *);
typedef void (*ShowInfoFunction) (FILE *outputFILE, void *);
typedef int (*CompareFunction) (void *, void *);
typedef int (*FindFunction) (void *, void *);

void DestroyList(TNodePointer *node,  FreeInfoFunction freeFunc, int destroyInfo); // free memory for the list
void DestroyNode(TNodePointer *node, FreeInfoFunction freeFunc, int destroyInfo); // free memory for the node
TNodePointer InitialiseNode(void *info); // (0/1) success or failure
void DisplayList(TNodePointer node, ShowInfoFunction showFunc, FILE *outputFILE);

int OrdererdInsert(TNodePointer *node, void *info, CompareFunction compFunc, int *position);

void* FindElement(TNodePointer node, void *toFind, FindFunction findFunction);

// (1 if it could remove the element, 0 otherwise)
int RemoveFromList(TNodePointer *node, void *info, FindFunction findFunction);

int InsertEnd(TNodePointer *node, void *info);

#endif