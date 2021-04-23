#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    void *info;
    struct node *next;
} TNode, *TNodePointer;


typedef void (*FreeInfoFunction) (void *);
typedef void (*ShowInfoFunction) (void *);
typedef int (*CompareFunction) (void *, void *);

void DestroyList(TNodePointer *node,  FreeInfoFunction freeFunc); // free memory for the list
void DestroyNode(TNodePointer *node, FreeInfoFunction freeFunc); // free memory for the node
TNodePointer InitialiseNode(void *info); // (0/1) success or failure
void DisplayList(TNodePointer node, ShowInfoFunction showFunc);

int OrdererdInsert(TNodePointer *node, void *info, CompareFunction compFunc);
