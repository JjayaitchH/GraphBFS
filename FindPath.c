//Jesus Hernandez
//jherna83
//PA4
//FindPath.c
//File that utilizes the Graph ADT to find shortest path 
//from one vertex to another

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
    if(argc > 3 || argc < 3)
    {
        printf("Usage: %s [inputFile] [outputFile]", argv[0]);
        exit(1);
    }

    FILE* inFile;
    FILE* outFile;

    inFile = fopen(argv[1], "r");
    outFile = fopen(argv[2], "w");

    if(inFile == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    else if(outFile == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int vertex;
    //grabs the value that represents the number of vertecies
    fscanf(inFile, "%d", &vertex);
    Graph G = newGraph(vertex);

    int u, v; //using the same veriables from Graph ADT to represent verticies

    //grab the values of the verticies and start adding the edges/verticies.
    while(fscanf(inFile, "%d %d", &u, &v) == 2)
    {
        if(u == 0 && v == 0)
        {
            break;
        }
        else
        {
            addEdge(G, u, v);
        }
    }

    printGraph(outFile, G);
    fprintf(outFile,"\n" );

    List L = newList();

    int source, destination;
    while(fscanf(inFile, "%d %d", &source, &destination) == 2)
    {
        if(source == 0 && destination == 0)
        {
            break;
        }

        BFS(G, source);
        getPath(L, G, destination);
        fprintf(outFile, "The distance from %d to %d is ", source, destination);
        if(length(L) == 0)
        {
            fprintf(outFile, "infinity\n");
            fprintf(outFile, "No %d-%d path exists\n", source, destination);
        }
        else
        {
            fprintf(outFile, "%d\n", getDist(G, destination));
            fprintf(outFile, "A shortest %d-%d path is: ", source, destination);
            printList(outFile, L);
            fprintf(outFile, "\n");
        }
        fprintf(outFile, "\n");
        clear(L);
    }
    freeList(&L);
    freeGraph(&G);
    fclose(inFile);
    fclose(outFile);
}