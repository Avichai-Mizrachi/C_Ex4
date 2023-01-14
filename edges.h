#ifndef edgesh
#define edgesh

// Edge
typedef struct edge_
{
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

typedef struct node_ node, *pnode;


void addEdge(int , int , int , pnode *);
void insertLastE(pnode, int , pnode *);
void deleteFromListE(int, pedge *, pnode *);
void addEdge(int, int, int, pnode *);
void freeEdges(pedge *);
edge *newEdge(int , pnode);

#endif