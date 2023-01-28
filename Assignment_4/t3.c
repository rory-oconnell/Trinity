#include <stdlib.h>
#include <stdio.h>
#include <limits.h>         // permits the use of INT_MAX as a stand in for infinity
#include "t3.h"
#define MAX_STRING_SIZE 50

BusStop *VertexArray[MAX_GRAPH];
Graph *g;
int num_vertices = 0;

// The CSV parser
int next_field(FILE *f, char *buf, int max)
{
    int i = 0, end = 0, quoted = 0;

    for (;;)
    {
        // fetch the next character from file
        buf[i] = fgetc(f);
        // if we encounter quotes then flip our state and immediately fetch next char
        if (buf[i] == '"')
        {
            quoted = !quoted;
            buf[i] = fgetc(f);
        }
        // end of field on comma if we're not inside quotes
        if (buf[i] == ',' && !quoted)
        {
            break;
        }
        // end record on newline or end of file
        if (feof(f) || buf[i] == '\n')
        {
            end = 1;
            break;
        }
        // truncate fields that would overflow the buffer
        if (i < max - 1)
        {
            ++i;
        }
    }

    buf[i] = 0; // null terminate the string
    return end; // flag stating whether or not this is end of the line
}

struct BusStop *get_stop(FILE *csv)
{
    char buf[MAX_STRING_SIZE];

    BusStop *p = malloc(sizeof(struct BusStop));

    next_field(csv, buf, MAX_STRING_SIZE); // load id into buffer as string
    p->StopID = atoi(buf);
    next_field(csv, p->Name, MAX_STRING_SIZE);
    next_field(csv, buf, MAX_STRING_SIZE); // load id into buffer as string
    p->Latitude = atof(buf);
    next_field(csv, buf, MAX_STRING_SIZE); // load id into buffer as string
    p->Longitude = atof(buf);

    return p;
}

struct Edge *get_edge(FILE *csv)
{
    char buf[MAX_STRING_SIZE];

    Edge *p = malloc(sizeof(struct BusStop));

    next_field(csv, buf, MAX_STRING_SIZE); // load id into buffer as string
    p->StopIDFrom = atoi(buf);
    next_field(csv, buf, MAX_STRING_SIZE);
    p->StopIDTo = atoi(buf);
    next_field(csv, buf, MAX_STRING_SIZE);
    p->weight = atoi(buf);                  // as the csv is given in char, conversion is needed using atoi

    return p;
}

void init_graph()
{
    g = malloc(sizeof(Graph));
    for (int i = 0; i < MAX_GRAPH; i++)
    {
        for (int j = 0; j < MAX_GRAPH; j++)
        {
            g->Arr[i][j] = 0;
        }
    }
}

void add_edge(Graph *g, int from, int to, int weight)
{
    g->Arr[from][to] = g->Arr[to][from] = weight;
}

//loads the edges from the CSV file of name fname
int load_edges(char *fname)
{
    FILE *f;
    int i = 0;
    int j = 0;
    int weight;
    int num_edges = 0;

    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f)
    {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    get_edge(f);
    init_graph();

    Edge *temp = malloc(sizeof(Edge));
    // read until the end of the file
    while (!feof(f))
    {
        temp = get_edge(f);
        i = temp->StopIDFrom;
        j = temp->StopIDTo;
        weight = temp->weight;
        add_edge(g, i, j, weight);
        num_edges++;
    }

    // always remember to close your file stream
    fclose(f);
    free(temp);
    printf("Loaded %d edges\n", num_edges);

    return 1;
}

//loads the vertices from the CSV file of name fname
int load_vertices(char *fname)
{
    FILE *f;
    num_vertices = 0;

    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f)
    {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    get_stop(f);
    BusStop *temp = malloc(sizeof(BusStop));
    // read until the end of the file
    while (!feof(f))
    {
        // VertexArray[num_vertices++] = get_stop(f);
        temp = get_stop(f);
        VertexArray[temp->StopID] = temp;
        num_vertices++;
    }
    temp = NULL;
    // always remember to close your file stream
    fclose(f);
    free(temp);
    printf("Loaded %d vertices\n", num_vertices);

    return 1;
}

int MinFunc(Graph *g, int dist[MAX_GRAPH], int bools[MAX_GRAPH])        // established if this is a minimum path
{
    int min = INT_MAX;
    int min_index;
    for (int v = 0; v < MAX_GRAPH; v++)
    {
        if (bools[v] == 0 && dist[v] < min)
        {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void dijkstra(Graph *g, int origin, int dest)
{
    int distance[MAX_GRAPH], shortestPath[MAX_GRAPH], prev[MAX_GRAPH];
    for (int i = 0; i < MAX_GRAPH; i++)
    {
        distance[i] = INT_MAX; //set distance to infinity
        shortestPath[i] = 0;   //and shortestPath to false
        prev[i] = 0;
    }
    distance[origin] = 0; // distance to the origin will always be 0;

    for (int eachNode = 0; eachNode < MAX_GRAPH; eachNode++)
    {
        int min_index = MinFunc(g, distance, shortestPath); //get min value of current set of unsearched vertices
        shortestPath[min_index] = 1;                        // set current index to true

        for (int Vertex = 0; Vertex < MAX_GRAPH; Vertex++)
        {
            if (!shortestPath[Vertex] && g->Arr[min_index][Vertex] && distance[min_index] != INT_MAX && distance[min_index] + g->Arr[min_index][Vertex] < distance[Vertex]) // if this is a shorter way of getting there
            {
                prev[Vertex] = min_index;
                distance[Vertex] = distance[min_index] + g->Arr[min_index][Vertex];     // establishing path
            }
        }
    }
    while (prev[dest] != origin)
    {
        printf("%d %s\n", VertexArray[prev[dest]]->StopID, VertexArray[prev[dest]]->Name);
        dest = prev[dest];
    }
}

void swap(int *a, int *b)       // Swaps pointers to values
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shortest_path(int startNode, int endNode)      // Prints the shortest path available between nodes

{
    swap(&startNode, &endNode);     // swap the start and end nodes as they will need to be returned in reverse order
    printf("%d %s\n", VertexArray[endNode]->StopID, VertexArray[endNode]->Name);    // print the starting node
    dijkstra(g, startNode, endNode);
    printf("%d %s\n", VertexArray[startNode]->StopID, VertexArray[startNode]->Name);
}

void free_memory(void)      // Free allocated memory
{
    free(g);
}