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
        adapter_cmd(answer, &graph);
    }
    delete_graph_cmd(&graph);
    return 0;
}