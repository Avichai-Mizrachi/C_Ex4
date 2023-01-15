#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


#include "graph.h"
#include "nodes.h"
#include "edges.h"


#define IN 999999

void choice(char answer, pnode *graph)
{
    switch (answer)
    {
    case 'A':
        build_graph(graph);
        break;

    case 'B':
        insert_node(graph);
        break;

    case 'D':
        delete_node(graph);
        break;

    case 'S':
        shortsPath(*graph);
        break;

    case 'T':
        TheShortestPath(*graph);
        break;

    default:
        if (answer == EOF)
        {
            return;
        }
    }
}

void build_graph(pnode *head)
{
    int count = 0;
    scanf("%d", &count);
    for (int i = 0; i < count; i++)
    {
        insertLastN(i, head);
    }
    char c = 0;
    while (scanf(" %c", &c) != 0)
    {
        if (c == 'n')
        {
            int src = -1;
            scanf("%d", &src);
            int dest, weight;
            while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0)
            {
                if (isalpha(dest))
                {
                    break;
                }
                addEdge(src, dest, weight, head);
            }
        }
        else
        {
            break;
        }
    }
    choice(c, head);
}

void insert_node(pnode *head)
{
    int ind;
    scanf("%d", &ind);
    int dest, weight;
    pnode newNode = getNode(head, ind);
    if (newNode == NULL)
    {
        insertLastN(ind, head);
        while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0)
        {
            if (isalpha(dest))
            {
                break;
            }
            addEdge(ind, dest, weight, head);
        }
    }
    else
    {
        pedge *pe = &(newNode->edges);
        freeEdges(pe);
        newNode->edges = NULL;
        while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0)
        {
            if (isalpha(dest))
            {
                break;
            }
            addEdge(ind, dest, weight, head);
        }
    }
    choice(getchar(), head);
}

void delete_graph(pnode *head)
{
    if (!head)
    {
        return;
    }
    pnode temp = *head;
    while (temp)
    {
        pedge nodeEdges = temp->edges;
        while (nodeEdges)
        {
            pedge edge = nodeEdges;
            nodeEdges = nodeEdges->next;
            free(edge);
        }
        pnode node = temp;
        temp = temp->next;
        free(node);
    }
    free(temp);
}

void delete_node(pnode *head)
{
    int ind;
    scanf("%d", &ind);

    pnode temp = *head;
    while (temp)
    {
        pedge *tempEdge = &(temp->edges);
        deleteFromListE(ind, tempEdge, head);
        temp = temp->next;
    }
    deleteFromListN(ind, head);
    choice(getchar(), head);
}

void shortsPath(pnode head)
{
    int src = 0, dst = 0;
    scanf("%d", &src);
    scanf("%d", &dst);
    printf("Dijsktra shortest path: %d \n", shortsPathFun(head, src, dst));
}

int shortsPathFun(pnode head, int source, int target)
{
    if (!head)
    {
        return -1;
    }
    pnode curr = head;
    int N = 0;
    while (curr)
    {
        if (N < curr->id)
        {
            N = curr->id;
        }
        curr = curr->next;
    }
    N += 1;
    int mat[N][N];

    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            mat[k][i] = IN;
        }
    }

    curr = head;
    while (curr)
    {
        pedge ed = curr->edges;
        while (ed)
        {
            mat[curr->id][ed->endpoint->id] = ed->weight;
            ed = ed->next;
        }
        curr = curr->next;
    }

    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (i == j)
                {
                    mat[i][i] = 0;
                }
                else if (i == k || j == k)
                {
                    mat[i][j] = mat[i][j];
                }
                else
                {
                    int val = mat[i][k] + mat[k][j];
                    if (mat[i][k] == 0 || mat[k][j] == 0)
                    {
                        val = 0;
                    }
                    mat[i][j] = min(mat[i][j], val);
                }
            }
        }
    }
    if (mat[source][target] == IN)
    {
        return -1;
    }
    return mat[source][target];
}

int min(int a, int b)
{
    return (a == 0) ? b : (b == 0) ? a
                      : (a < b)    ? a
                                   : b;
}

void TheShortestPath(pnode head)
{
    int count;
    scanf("%d", &count);
    if (count == 0)
    {
        return;
    }
    int cities[count];
    for (size_t i = 0; i < count; i++)
    {
        scanf("%d", &cities[i]);
    }
    int fac = factorial(count);
    int perm[fac];
    int temp = 0;
    permutation(head, cities, 0, count - 1, perm, &temp);
    int ind = find_minimum(perm, fac);
    if (perm[ind] == IN)
    {
        printf("TSP shortest path: %d \n", -1);
    }
    else
    {
        printf("TSP shortest path: %d \n", perm[ind]);
    }
}

int calcArray(pnode head, int cities[], int size)
{
    int distance = 0;
    for (size_t i = 0; i < size - 1; i++)
    {
        int path = shortsPathFun(head, cities[i], cities[i + 1]);
        if (path == -1)
        {
            return IN;
        }
        distance += path;
    }
    return distance;
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void permutation(pnode head, int *cities, int start, int end, int *perm, int *ind)
{
    if (start == end)
    {
        perm[(*ind)++] = calcArray(head, cities, end + 1);
        return;
    }
    int i;
    for (i = start; i <= end; i++)
    {
        swap((cities + i), (cities + start));
        permutation(head, cities, start + 1, end, perm, ind);
        swap((cities + i), (cities + start));
    }
}

int find_minimum(int arr[], int n)
{
    int index = 0;
    for (int i = 1; i < n; i++)
        if (arr[i] < arr[index])
        {
            index = i;
        }
    return index;
}

int factorial(int num)
{
    if (num < 0)
    {
        return 0;
    }
    if (num == 0)
        return 1;
    return factorial(num - 1) * num;
}