#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "edges.h"
#include "graph.h"

int main()
{
    pnode graph = NULL;
    char in;
    while (scanf(" %c", &in) != EOF){
        adapter_cmd(in, &graph);
    }
    delete_graph_cmd(&graph);
    return 0;
}