#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "nodes.h"
#include "edges.h"
#include "graph.h"

#define IN 999999

void choice(char answer, pnode *graph)
{
    switch (answer)
    {
    case 'A':
        build_graph_cmd(graph);
        break;

    case 'B':
        insert_node_cmd(graph);
        break;

    case 'D':
        delete_node_cmd(graph);
        break;

    case 'S':
        shortsPath_cmd(*graph);
        break;

    case 'T':
        TSP_cmd(*graph);
        break;

    default:
        if (answer == EOF)
        {
            return;
        }
    }
}

void build_graph_cmd(pnode *head)
{
    // delete_graph_cmd(head);
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
    // printf("built graph\n");
    // printGraph_cmd(head);
    choice(c, head);
}

void insert_node_cmd(pnode *head)
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
    // printf("added node\n");
    // printGraph_cmd(head);
    choice(getchar(), head);
}

void delete_graph_cmd(pnode *head)
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

void delete_node_cmd(pnode *head)
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
    // printf("deleted node\n");
    // printGraph_cmd(head);
    choice(getchar(), head);
}

void printGraph_cmd(pnode *head)
{ // for self debug
    if (!head)
    {
        return;
    }
    pnode temp = *head;
    while (temp)
    {
        printf("Node{%d} -- Edges{", temp->id);
        pedge ed = temp->edges;
        while (ed != NULL)
        {
            printf("%d -> %d -- %d,  ", temp->id, ed->endpoint->id, ed->weight);
            ed = ed->next;
        }
        temp = temp->next;
        printf("}\n");
    }
    printf("\n");
}

void shortsPath_cmd(pnode head)
{
    int src = 0, dst = 0;
    scanf("%d", &src);
    scanf("%d", &dst);
    printf("Dijsktra shortest path: %d \n", shortsPath(head, src, dst));
}

int shortsPath(pnode head, int source, int target)
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
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

void TSP_cmd(pnode head)
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
        int path = shortsPath(head, cities[i], cities[i + 1]);
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
        // swapping numbers
        swap((cities + i), (cities + start));
        // fixing one first digit and calling permutation on the rest of the digits
        permutation(head, cities, start + 1, end, perm, ind);
        swap((cities + i), (cities + start));
    }
}

// factorial
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

// finding minimum in an array
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