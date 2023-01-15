#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "edges.h"
#include "graph.h"

int main()
{
    pnode graph = NULL;
    char answer;
    while (scanf(" %c", &answer) != EOF){
        choice(answer, &graph);
    }
    delete_graph(&graph);
    return 0;
}