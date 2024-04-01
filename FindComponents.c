// /****************************************************************************************
// *  FindComponents.c
// *  Determines strongly connected components of initialized digraph
// *****************************************************************************************/

#include "Graph.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        fprintf(stderr, "Invalid number of command line arguments\n");
        exit(EXIT_FAILURE);
    }
    FILE *output = fopen(argv[2],"w");
    FILE *input = fopen(argv[1], "r");
    if (input == NULL){
        // fclose(input);
        fclose(output);
        fprintf(stderr, "Invalid file\n");
        exit(EXIT_FAILURE);
    }

    char str_vertices[100];
    fgets(str_vertices,100,input);
    int vertices = atoi(str_vertices);

    Graph G = newGraph(vertices);
    List S = newList();
    for(int i=1; i<=vertices; i++){
        append(S, i);
    } 
    
    char str_u[100];        //string of fist vertex
    char str_v[100];        //string of second vertex
    int u;          //fist vertex
    int v;          //second vertex
    while (1){
        fscanf(input, "%s", str_u);
        fscanf(input, "%s", str_v);
        u = atoi(str_u);
        v = atoi(str_v);
        if(u == 0){
            break;
        }
        addArc(G,u,v);
    }

    fprintf(output,"Adjacency list representation of G:\n");
    printGraph(output,G);
    fprintf(output, "\n");

    DFS(G,S);
    Graph Gt = transpose(G);
    DFS(Gt,S);


    // loop determines number of strongly connected components
    int num_scc = 0;
    for (int i = 1; i <= G->order; i++){
        if (Gt->parent[i] == 0 ){        //determine if vertex has not children in DFS tree
            num_scc++;
        }
    }

    fprintf(output, "G contains %d strongly connected components:\n", num_scc);
    // outputs the strongly connected components topologically sorted
    List components = newList();
    int component_num = 1;
    for (moveBack(S); index(S) >= 0; movePrev(S)){
        prepend(components,get(S));
        if (Gt->parent[get(S)] == 0 ){        //determine if vertex has not children in DFS tree
            fprintf(output,"Component %d: ",component_num++);
            printList(output,components);
            fprintf(output,"\n");
            clear(components);

        }
    }


    freeList(&components);
    freeList(&S);
    freeGraph(&Gt);
    freeGraph(&G);
    fclose(input);
    fclose(output);
}

