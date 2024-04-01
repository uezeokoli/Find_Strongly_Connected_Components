// /****************************************************************************************
// *  GraphTest.c
// *  Tests functionality for Graph ADT
// *****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


void TestFunctions(){
   //Test getOrder()
   Graph G = newGraph(20);
   assert(getOrder(G) == 20);
   freeGraph(&G);
   printf("getOrder() works!\n");
   //Test getSize()
   G = newGraph(20);
   assert(G->size == 0);
   addEdge(G,1,2);
   addEdge(G,1,3);
   assert(G->size == 2);
   freeGraph(&G);
   printf("getSize() works!\n");
   //Test addEdge()
   G = newGraph(20);
   assert(G->size == 0);
   assert(length(G->neighbors[1]) == 0);
   addEdge(G,1,2);
   addEdge(G,1,3);
   assert(G->size == 2);
   addEdge(G,1,4);
   addEdge(G,1,5);
   assert(G->size == 4);
   assert(length(G->neighbors[1]) != 0);
   assert(length(G->neighbors[2]) != 0);
   freeGraph(&G);
   printf("addEdge() works!\n");
   //Test addArc
   G = newGraph(20);
   assert(G->size == 0);
   assert(length(G->neighbors[1]) == 0);
   addArc(G,1,2);
   addArc(G,1,3);
   assert(G->size == 2);
   addArc(G,1,4);
   addArc(G,1,5);
   assert(G->size == 4);
   assert(length(G->neighbors[1]) != 0);
   assert(length(G->neighbors[2]) == 0);
   freeGraph(&G);
   printf("addArc() works!\n");
   //Test DFS()
   G = newGraph(20);
   List S = newList();
   assert(G->finish[2] == UNDEF);
   assert(G->discover[2] == UNDEF);
   assert(G->parent[2] == NIL);
   assert(G->color[2] == white);
   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   for (int i = 1; i <= 7; i++){
      append(S,i);
   }
   DFS(G,S);
   assert(G->finish[2] != UNDEF);
   assert(G->discover[2] != UNDEF);
   assert(G->parent[2] != NIL);
   assert(G->color[2] != white);
   freeGraph(&G);
   freeList(&S);
   printf("DFS() works!\n");
   //Test getParent() 
   G = newGraph(20);
   S = newList();
   assert(getParent(G,2) == NIL);
   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   for (int i = 1; i <= 7; i++){
      append(S,i);
   }
   DFS(G,S);
   assert(getParent(G,2) != NIL);
   freeGraph(&G);
   freeList(&S);
   printf("getParent() works!\n");
   //Test getDiscover() 
   G = newGraph(20);
   S = newList();
   assert(getDiscover(G,1) == UNDEF);
   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   for (int i = 1; i <= 7; i++){
      append(S,i);
   }
   DFS(G,S);
   assert(getDiscover(G,1) != UNDEF);
   freeGraph(&G);
   freeList(&S);
   printf("getDiscover() works!\n");
   //Test getFinish()
   G = newGraph(20);
   S = newList();
   assert(getFinish(G,1) == UNDEF);
   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   for (int i = 1; i <= 7; i++){
      append(S,i);
   }
   DFS(G,S);
   assert(getFinish(G,1) != UNDEF);
   freeGraph(&G);
   freeList(&S);
   printf("getFinish() works!\n");

   //All Functions work
   printf("All Functions are working!\n");


}


int main(int argc, char* argv[]){

   TestFunctions();

}
