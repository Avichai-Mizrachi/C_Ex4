#include <stdio.h>
#include <stdlib.h>

#include "edges.h"
#include "nodes.h"
#include "graph.h"

node *newNode(int id)
{
    pnode p = (pnode)malloc(sizeof(node));
    if (p == NULL)
    {
        return NULL;
    }
    p->id = id;
    p->next = NULL;
    p->edges = NULL;
    return p;
}

void insertLastN(int id, pnode *head)
{
    pnode *p = head;
    while (*p)
    {
        p = &((*p)->next);
    }
    *p = newNode(id);
}

void deleteFromListN(int id, pnode *head)
{
    pnode h = *head;
    pnode p = NULL;
    if(h->id != id){
        while (h->next->id != id)
        {
            h = h->next;
        }
        p = h->next;
        h->next = h->next->next;
        freeEdges(&(p->edges));
        free(p);
    }
    else{
        p = *head;
        *head = p->next;
        freeEdges(&(p->edges));
        free(p);
    }
}

pnode getNode(pnode *head, int id)
{
    pnode h = *head;
    while (h)
    {
        if (h->id == id)
        {
            return h;
        }
        h = h->next;
    }
    return NULL;
}