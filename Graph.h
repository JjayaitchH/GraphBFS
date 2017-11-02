//Jesus Hernandez
//jherna83
//PA4
//Graph.h
//Header file for Graph

#ifndef _GRAPH_H_INCLUDE
#define _GRAPH_H_INCLUDE

#include <stdio.h>
#include "List.h"

#define INF -420
#define NIL -69

typedef struct GraphObj* Graph;

//~~~Constructors and Destructors~~~
Graph newGraph(int n);
void freeGraph(Graph* pG);

//~~~Access Functions~~~
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

//~~~Manipulation Functions~~~
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

//~~~Other functions~~~
void printGraph(FILE* out, Graph G);
void place(List L, int u);
#endif