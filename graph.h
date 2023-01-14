#ifndef GRAPH_
#define GRAPH_

#include "nodes.h"
#include "edges.h"
// Graph

// --------------------------------------- //
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode *head); //for self debug
void delete_graph_cmd(pnode *head);
void shortsPath_cmd(pnode head);
int shortsPath(pnode head, int, int);
int min(int, int);

void TSP_cmd(pnode head);
void permutation(pnode, int *, int, int, int*, int*);
int calcArray(pnode, int[], int);
void swap(int *, int *);
int factorial(int);
int find_minimum(int[], int);

void adapter_cmd(char, pnode *head);


#endif
