// /****************************************************************************************
// *  Ugonna Ezeokoli
// *  uezeokol
// *  2024 Winter CSE101 PA3 
// *  Graph.h
// *  declare functions and construct the Graph 
// *****************************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include "List.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define UNDEF -1
#define NIL  0
#define white 2
#define gray  1
#define black 0


typedef struct GraphObj* Graph;

typedef struct GraphObj {
    List *neighbors;
    int* discover;
    int* parent;
    int* finish;
    int* color;
    int order;
    int size;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
int Visit(Graph G, List S,List headlist, int time);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif