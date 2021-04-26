/* MIHAILEACU Eduard-Florin - 312CB */
#include "TLista.h"

void DestroyNode(TNodePointer *node, FreeInfoFunction freeFunc, int destroyInfo)
{
    if(*node != NULL)
    {
        if(destroyInfo == 1)
            freeFunc((*node)->info);
        free(*node);
        *node = NULL;
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
            return node->info;
        }
        node = node->next;
    }
    return NULL;
}

void DisplayList(TNodePointer node, ShowInfoFunction showFunc, FILE *outputFILE)
{
    fprintf(outputFILE,"[");
    while(node != NULL)
    {
        showFunc(outputFILE, node->info);
        if(node->next != NULL)
            fprintf(outputFILE,", ");
        node = node->next;
    }
    fprintf(outputFILE,"].\n");
}

// remove from the list the node with the specified info without freeing the info
int RemoveFromList(TNodePointer *node, void *info, FindFunction findFunction)
{
    // search for the node
    TNodePointer aux = *node;
    if(aux == NULL)
        return 0;

    // if it is the first node
    if(findFunction(aux->info, info) == 1)
    {
        *node = (*node)->next;
        free(aux);
        return 1;
    }

    while(aux->next != NULL)
    {
        if(findFunction(aux->next->info, info) == 1)
        {
            TNodePointer u = aux->next;
            aux->next = aux->next->next;
            free(u);
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

int InsertEnd(TNodePointer *node, void *info)
{
    TNodePointer newNode = InitialiseNode(info);

    if(newNode == NULL)
    {
        printf("Eroare la alocare nod!\n");
        return 0;
    }

    if(*node == NULL)
    {
        *node = newNode;
    }
    else
    {
        TNodePointer aux = *node;
        while(aux->next != NULL) // go to the last element
        {
            aux = aux->next;
        }
        aux->next = newNode;
    }
    return 1;
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