// /****************************************************************************************
// *  Ugonna Ezeokoli
// *  uezeokol
// *  2024 Winter CSE101 PA3 
// *  Graph.c
// *  Defines functions for Graph ADT
// *****************************************************************************************/


#include "Graph.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



/*** Constructors-Destructors ***/
Graph newGraph(int n){
    if (0 > n){
        fprintf(stderr,"Graph Error: Vertices can not be negative\n");
        exit(EXIT_FAILURE);
    }

    Graph new_graph = malloc(sizeof(GraphObj));
    new_graph->neighbors = (List *) calloc(n+1, sizeof(List));
    new_graph->discover = (int *) calloc(n+1, sizeof(int));
    new_graph->parent = (int *) calloc(n+1, sizeof(int));
    new_graph->finish = (int *) calloc(n+1, sizeof(int));
    new_graph->color = (int *) calloc(n+1, sizeof(int));
    new_graph->order = n;
    new_graph->size = 0;

    for(int i = 1; i<=(n);i++){
        new_graph->neighbors[i] = newList();
        new_graph->discover[i] = UNDEF ;
        new_graph->parent[i] = NIL ;
        new_graph->finish[i] = UNDEF;
        new_graph->color[i] = white;
    }
    return new_graph;
}
void freeGraph(Graph* pG){
    if(pG!=NULL && *pG!=NULL) { 
        Graph G = *pG;
        for (int i = 1; i <= G->order; i++){
            freeList(&G->neighbors[i]);
        }
        free(G->neighbors);
        free(G->discover);
        free(G->finish);
        free(G->parent);
        free(G->color);
        free(*pG);
        *pG = NULL;
    }

}
/*** Access functions ***/
int getOrder(Graph G){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}
int getSize(Graph G){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

//precondition 1 ≤ 𝑢 ≤ getOrder(𝐺). 
int getParent(Graph G, int u){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > G->order){
        fprintf(stderr,"Graph Error: calling getParent() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}
//precondition 1 ≤ 𝑢 ≤ getOrder(𝐺). 
int getDiscover(Graph G, int u){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (1 > u || u > G->order){
        fprintf(stderr,"Graph Error: calling getDiscover() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];

}

//precondition 1 ≤ 𝑢 ≤ getOrder(𝐺). 
int getFinish(Graph G, int u){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (1 > u || u > G->order){
        fprintf(stderr,"Graph Error: calling getFinish() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];

}

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }

    if ((1 > u || u > G->order) || (1 > v || v > G->order)){
        fprintf(stderr,"Graph Error: calling addEdge() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }

    if (u <= G->order && v <=G->order){
        G->size--;
        //adding v to adj[u] list
        addArc(G,u,v);
        //adding u to adj[v] list
        addArc(G,v,u);
    }
}
void addArc(Graph G, int u, int v){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }

    if ((1 > u || u > G->order) || (1 > v || v > G->order)){
        fprintf(stderr,"Graph Error: calling addArc() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }

    for (moveFront(G->neighbors[u]); index(G->neighbors[u]) >= 0; moveNext(G->neighbors[u])){
        if (get(G->neighbors[u]) == v){
            return;
        }
    }
    if (u <= G->order && v <=G->order){
        // adding v to adj[u] list
        G->size++;
        if (length(G->neighbors[u]) == 0){
            append(G->neighbors[u],v);
        }
        else{
            moveFront(G->neighbors[u]);
            for (int x = 0; x<length(G->neighbors[u]);x++){
                if(v < get(G->neighbors[u])){
                    insertBefore(G->neighbors[u],v);
                    break;
                }
                if(x == length(G->neighbors[u])-1){
                    insertAfter(G->neighbors[u], v);
                    break;
                }
                moveNext(G->neighbors[u]);
            }
        }
    }
}

void DFS(Graph G, List S){
    int remove_elements = S->size;              //how many elements to DeleteFront
    for (moveFront(S); index(S)>= 0; moveNext(S)){
        G->color[get(S)] = white;
        G->parent[get(S)] = NIL;
    }
    int time = 0;
    for (moveFront(S); index(S)>= 0; moveNext(S)){      //main loop of DFS
        if (G->color[get(S)] == white){
            time = Visit(G,S,S,time);
        }
    }
    for (int i = 0; i < remove_elements ; i++){
        deleteBack(S);
    }

}

int Visit(Graph G, List S, List headlist,int time){
    G->discover[get(S)] = ++time;       //discover x
    G->color[get(S)] = gray;
    for (moveFront(G->neighbors[get(S)]);index(G->neighbors[get(S)]) >= 0;moveNext(G->neighbors[get(S)])){
        if (G->color[get(G->neighbors[get(S)])] == white ){
            G->parent[get(G->neighbors[get(S)])] = get(S);
            time = Visit(G, G->neighbors[get(S)] , headlist, time);
        }
    }
    G->color[get(S)] = black;
    G->finish[get(S)] = ++time;
    prepend(headlist,get(S));
    return time;

}

/*** Other operations ***/
Graph transpose(Graph G){
    if( G == NULL ){
      fprintf(stderr,"Graph Error: calling copyGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    Graph Gt = newGraph(G->order);
    for(int i = 1; i<=(G->order);i++){
        for (moveFront(G->neighbors[i]); index(G->neighbors[i]) >= 0; moveNext(G->neighbors[i])){
            append(Gt->neighbors[get(G->neighbors[i])],i);
        }
    }
    return Gt;
}
Graph copyGraph(Graph G){
    if( G == NULL ){
      fprintf(stderr,"Graph Error: calling copyGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    Graph copy = malloc(sizeof(GraphObj));
    copy->neighbors = (List *) calloc(G->order+1, sizeof(List));
    copy->discover = (int *) calloc(G->order+1, sizeof(int));
    copy->parent = (int *) calloc(G->order+1, sizeof(int));
    copy->finish = (int *) calloc(G->order+1, sizeof(int));
    copy->color = (int *) calloc(G->order+1, sizeof(int));
    copy->order = G->order;
    copy->size = 0;

    for(int i = 1; i<=(G->order);i++){
        copy->neighbors[i] = copyList(G->neighbors[i]);
        copy->discover[i] = G->discover[i];
        copy->parent[i] = G->parent[i];
        copy->finish[i] = G->finish[i];
        copy->color[i] = G->color[i];
    }
    return copy;

}

void printGraph(FILE* out, Graph G){
    if (G != NULL){
        for (int i = 1; i <= G->order;i++){
            fprintf(out,"%d: ",i);
            printList(out, G->neighbors[i]);
            fprintf(out,"\n");
        }
    }
}

