Ugonna Ezeokoli 
uezeokol
2024 Winter CSE101 PA3 
README.md

Files:

1. List.h:
    header file which is used to declare functions and construct the ADTs Node and List
2. List.c:
    C source file which is used to define the declared functions and incoporates the List and Node ADT
3. Graph.h
    header file which is used to declare functions and construct the Graph ADT
4. Graph.c
    C source file which is used to define the declared functions and incoporates the Graph, List, and Node ADT
5. GraphTest.c:
    C source file which is used to determine if defined functions in Graph.c are working as expected
6. FindComponents.c:
    C source file which takes two command line arguments(input file to read and name for output file) and reads the input file to initiliaze a digraph by adding Arcs. This file is also responsible for outputting the adjacency lists and strongly connected components of the graph.
7. Makefile:
    makefile which compiles code and creates executables FindComponents and GraphTest. Can also check for memory errors in FindComponents and GraphTest with command checkTest and checkFind. 