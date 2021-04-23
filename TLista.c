#include "TLista.h"

void DestroyNode(TNodePointer *node, FreeInfoFunction freeFunc)
{
    freeFunc((*node)->info);
    free(*node);
    *node = NULL;
}

void DestroyList(TNodePointer *node, FreeInfoFunction freeFunc)
{
    while(*node != NULL)
    {
        TNodePointer aux = *node;
        (*node) = (*node)->next;
        DestroyNode(&aux, freeFunc);
    }
}

TNodePointer InitialiseNode(void *info)
{
    TNodePointer node = (TNodePointer) malloc(sizeof(TNode));
    if(node == NULL)
    {
        printf("Eroare alocare nod");
        return NULL;
    }

    node->info = info;
    node->next = NULL;

    return node;
}

void DisplayList(TNodePointer node, ShowInfoFunction showFunc)
{
    if(node == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        showFunc(node->info);
        DisplayList(node->next, showFunc);
    }
}

int OrdererdInsert(TNodePointer *node, void *info, CompareFunction compFunc)
{
    TNodePointer newNode = InitialiseNode(info);
    if(newNode == NULL)
    {
        printf("Eroare la alocare nod!\n");
        return 0;
    } 
    if(*node == NULL) // the first element
    {
        *node = newNode;
    }
    else
    {
        TNodePointer aux = *node, previous = NULL;
        while(aux != NULL && compFunc(info, aux->info) < 0) // we find where to insert the element
        {
            previous = aux;
            aux = aux->next;
        }

        if(previous == NULL) // first element
        {
            newNode->next = aux;
            *node = newNode;
        }
        else// we insert before aux;
        {
            newNode->next = aux;
            previous->next = newNode;
        }
    }
    return 1;
}