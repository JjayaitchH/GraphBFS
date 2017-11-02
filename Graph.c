//Jesus Hernandez
//jherna83
//PA4
//Graph.c

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
//#include "List.h"

//void place(List L, int u);

typedef struct GraphObj
{
    char* color;
    int*  parentV;
    int* distance;
    List* row;
    int source;
    int size;
    int order;
}GraphObj;
//~~~Consructors and Destructors~~~

//returns Graph pointing to newly created GraphObj
//n = number ov verticies
//contains no edges
Graph newGraph(int n)
{
    if(n < 1)
    {
        printf("Error when calling newGraph. order of graph cannot be less than 1");
        exit(1);
    }
    Graph G = malloc(sizeof(GraphObj));

    G -> color = malloc((n + 1) * sizeof(char));
    G -> parentV = malloc((n + 1) * sizeof(int));
    G -> distance = malloc((n + 1) * sizeof(int));
    G -> row = malloc((n + 1) * sizeof(List));

    for(int i = 1; i <= n; i++)
    {
        G -> color[i] = 'w';
        G -> parentV[i] = NIL;
        G -> distance[i] = INF;
        G -> row[i] = newList();
    }

    G -> source = NIL;
    G -> size = 0;
    G -> order = n;

    return G;
}

//free all dynamic memory in Graph
void freeGraph(Graph* pG)
{
    if(pG != NULL && *pG != NULL)
    {


        for(int i = 1; i <= getOrder(*pG); i++)
        {
            freeList(&(*pG) -> row[i]);
        }
        free((*pG) -> color);
        free((*pG) -> parentV);
        free((*pG) -> distance);
        free((*pG) -> row);

        free(*pG);
        *pG = NULL;
    }
}
//~~~End Constructors and Destructors

//~~~Access Functions~~~
//returns the order of the graph
//Pre: Graph must not be NULL
int getOrder(Graph G)
{
    if(G == NULL)
    {
        printf("Error when calling getOrder. Graph is NULL\n");
        exit(1);
    }
    return G -> order;
}

//returns the size of the Graph
//Pre: Graph must not be NULL
int getSize(Graph G)
{
    if(G == NULL)
    {
        printf("Error when calling getSize. Graph is NULL\n");
        exit(1);
    }
    return G -> size;
}

//returns source vertex of Graph
//Pre: Graph must not be NULL
int getSource(Graph G)
{
    if(G == NULL)
    {
        printf("Error when calling getSource. Graph is NULL\n");
        exit(1);
    }
    return G -> source;
}

//will return the parent of vertex u
//Pre: Graph must not be NULL and vertex u cannot be greater than order or less than 1
int getParent(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Error when calling getParent. Graph is NULL\n");
        exit(1);
    }
    else if(u > getOrder(G) || u < 1)
    {
        printf("Error when calling getParent. Vertex is invalid\n");
        exit(1);
    }
    return G -> parentV[u];
}

//returns distance from most recent BFS source to vertex u
//or return INF if BFS has not been called
//pre: Graph must not be NULL and vertex u cannot be greater than order or less than 1
int getDist(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Error when calling getDist. Graph is NULL\n");
        exit(1);
    }
    else if(u > getOrder(G) || u < 1)
    {
        printf("Error when calling getDist. Vertex is invalid\n");
        exit(1);
    }
    return G -> distance[u];
}

//appends shortest path to u to list L or NIL if there is none 
//pre: Graph must not be NULL and vertex u cannot be greater than order or less than 1 and source cannot be NIL
void getPath(List L, Graph G, int u)
{
    if(G == NULL)
    {
        printf("Error at getPath. Graph is NULL\n");
        exit(1);
    }   
    else if(u > getOrder(G) || u < 1)
    {
        printf("Error when calling getPath. Vertex is invalid\n");
        exit(1);
    }
    else if(getSource(G) == NIL)
    {
        printf("Error when calling getPath. BFS must be called first.\n");
    }

    if(u == getSource(G))
    {
        append(L, u);
    }
    else if(G -> parentV[u] != NIL)
    {
        getPath(L, G, G -> parentV[u]);
        append(L, u);
    }
}
//~~~End Access Functions 

//~~~Start Manipulation Functions~~~
//returns graph to its original null graph state
//pre: Graph must not be NULL 
void makeNull(Graph G)
{
    if(G == NULL)
    {
        printf("Error when calling makeNull. Graph is NULL\n");
        exit(1);
    }

    for(int i = 1; i <= getOrder(G); i++)
    {
        clear(G -> row[i]);
    }

    G -> size = 0;
}

//inserts new edge joining u and v
////pre: Graph must not be NULL and vertex u and v cannot be greater than order or less than 1
void addEdge(Graph G, int u, int v)
{
    if(G == NULL)
    {
        printf("Error when calling addEdge. Graph is NULL\n");
        exit(1);
    }
    else if(u > getOrder(G) || u < 1)
    {
        printf("Error when calling addEdge. Invalid Vertex\n");
        exit(1);
    }
    else if(v > getOrder(G) || v < 1)
    {
        printf("Error when calling addEdge. Invalid Vertex\n");
        exit(1);
    }

    List tempU = G -> row[u];
    place(tempU, v);

    List tempV = G -> row[v];
    place(tempV, u);

    G -> size++;
}

//add new directed edge from u to v
//pre: Graph must not be NULL and vertex u and v cannot be greater than order or less than 1
void addArc(Graph G, int u, int v)
{
    if(G == NULL)
    {
        printf("Error when calling addArc. Graph is NULL\n");
        exit(1);
    }
    else if(u > getOrder(G) || u < 1)
    {
        printf("Error when calling addArc. Invalid Vertex\n");
        exit(1);
    }
    else if(v > getOrder(G) || v < 1)
    {
        printf("Error when calling addArc Invalid Vertex\n");
        exit(1);
    }

    List temp = G -> row[u];
    place(temp, v);

    G -> size++;
}

//the BFS algorithm
//pre: Graph must not be NULL
void BFS(Graph G, int s)
{
    if(G == NULL)
    {
        printf("Error when calling printGraph. Graph is NULL\n");
        exit(1);
    }

    for(int i = 1; i <= getOrder(G); i++)
    {
        G -> color[i] = 'w';
        G -> distance[i] = INF;
        G -> parentV[i] = NIL;
    }
    G -> source = s;
    G -> color[s] = 'g';
    G -> distance[s] = 0;
    G -> parentV[s] = NIL;

    List newL = newList();

    append(newL, s);

    while(length(newL) != 0)
    {
        int x = front(newL);
        deleteFront(newL);
        List L = G -> row[x];
        if(length(L) != 0)
        {
            for(moveFront(L); index(L) != -1; moveNext(L))
            {
                int y = get(L);
                if(G -> color[y] == 'w')
                {
                    G -> color[y] = 'g';
                    G -> distance[y] = G -> distance[x] + 1;
                    G -> parentV[y] = x;
                    append(newL, y);
                }
            G -> color[x] = 'b';
            }
        }
    }
    freeList(&newL);
}

//~~~Other functions~~~
//function printGraph prints out the graph
//pre: Graph must not be NULL
void printGraph(FILE* out, Graph G)
{
    if(G == NULL)
    {
        printf("Error when calling printGraph. Graph is NULL\n");
        exit(1);
    }
    for(int i = 1; i <= getOrder(G); i++)
    {
        List L = G -> row[i];
        fprintf(out, "%d: ", i);
        printList(out, L);
        fprintf(out, "\n");
    }
}

//this is a helper function I made that helps place a vertex
//in a list. I used this code for both addEdge and addArc but realized
//it would look much better if I made an actual funtion 
void place(List L, int u)
{
    if(length(L) == 0)
    {
        append(L, u);
        return;
    }

    moveFront(L);
    while(index(L) >= 0)
    {
        if(get(L) < u)
        {
            moveNext(L);
        }
        else
        {
            break;
        }
    }
    if(index(L) != -1)
    {
        insertBefore(L, u);
    }
    else
    {
        append(L, u);
    }
}