#include "TLista.h"

void DestroyNode(TNodePointer *node, FreeInfoFunction freeFunc, int destroyInfo)
{
    if(*node != NULL)
    {
        if(destroyInfo == 1)
            freeFunc((*node)->info);
        free(*node);
    }
}

void DestroyList(TNodePointer *node, FreeInfoFunction freeFunc, int destroyInfo)
{
    while(*node != NULL)
    {
        TNodePointer aux = *node;
        (*node) = (*node)->next;
        DestroyNode(&aux, freeFunc, destroyInfo);
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

void* FindElement(TNodePointer node, void *toFind,  FindFunction findFunction)
{
    while(node != NULL)
    {
        if(findFunction(node->info, toFind) == 1)
        {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void DisplayList(TNodePointer node, ShowInfoFunction showFunc, FILE *outputFILE)
{
    if(node != NULL)
    {
        fprintf(outputFILE,"[");
    }
    while(node != NULL)
    {
        showFunc(outputFILE, node->info);
        if(node->next != NULL)
            fprintf(outputFILE,", ");
        node = node->next;
    }
    fprintf(outputFILE,"].\n");

}

int OrdererdInsert(TNodePointer *node, void *info, CompareFunction compFunc, int *position)
{
    TNodePointer newNode = InitialiseNode(info);
    *position = 1;
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
            (*position)++;
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