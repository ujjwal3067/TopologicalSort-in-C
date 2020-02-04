#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "topological_sort.h"

// Color definition
// 1 -> WHITE
// 2 -> GRAY
// 3 -> BALCK

// Insert a new vertex to a linked list
AdjList insert_vertex(AdjList adjList, int vertex)
{
    // Temporary node used to travel the linked list
    AdjListNodePtr cur = (AdjListNodePtr)malloc(sizeof(AdjListNode));
    // The new vertex
    AdjListNodePtr new = (AdjListNodePtr)malloc(sizeof(AdjListNode));
    new->vertex = vertex;
    new->next = NULL;
    // Check if the linked list exist
    if (adjList)
    {
        // When the linked list exist, reach the end of it
        cur = adjList;
        while (cur->next)
        {
            cur = cur->next;
        }
        cur->next = new; // add the new vertex to the end
    }
    else
    {
        // When the linked list does not exist, create a new one
        adjList = new;
    }
    return adjList; // Return the modified linked list
}

// Construct the graph from the input file
AdjList *construct_adjlist(const char *filename, AdjList *adjList, int *numVert)
{
    // Allocate space for adjList
    adjList = (AdjList *)calloc(60, sizeof(AdjList));
    FILE *ifp;
    int count = 0; // Count the number of vertices
    // Check if the input is valid
    if ((ifp = fopen(filename, "r")) == NULL)
    {
        printf("Invalid file name!");
        fflush(stdout);
        fclose(ifp);
        exit(EXIT_FAILURE);
    }
    // For each line
    char line[1024];
    while (fgets(line, sizeof line, ifp) != NULL)
    {
        int src_vertex, dst_vertex;
        char *pch;
        // Read the line
        pch = strtok(line, " \n\r");
        sscanf(pch, "%d", &src_vertex);
        pch = strtok(NULL, " \n\r");
        while (pch != NULL) // While not reached to the end
        {
            sscanf(pch, "%d", &dst_vertex);
            // Add the vertex to the list
            adjList[src_vertex] = insert_vertex(adjList[src_vertex], dst_vertex);
            pch = strtok(NULL, " \n\r");
        }
        count++;
    }
    fclose(ifp);
    *numVert = count; // Total number of vertices
    return adjList;
}

// DFS Visit
void dfs_visit(int i, AdjList *graph, int numVer, int *color, int *result)
{
    static int cnt = 1;       // Keep track of the "time"
    AdjList hnode = graph[i]; // Extract the linked list of vertex i
    color[i] = 1;             // Update the color
    while (hnode)
    {
        int cur = hnode->vertex;       // current operating vertex
        if (color[hnode->vertex] == 1) // Check if the edge is a back edge
        {
            printf("This graph has a cycle!\n");
            exit(0);
        }
        if (color[hnode->vertex] == 0) // Explore the white vertex
        {
            // Recursion
            dfs_visit(hnode->vertex, graph, numVer, color, result);
        }
        // Proceed to the next node
        hnode = hnode->next;
    }
    // Update the color and the finish time
    color[i] = 2;
    result[cnt] = i;
    cnt += 1;
}

// DFS
void dfs(AdjList *graph, int numVer, int *result)
{
    int i;
    int *color;
    color = (int *)malloc((numVer + 1) * sizeof(int)); // Allocate the menory
    // Initialize all the vertices
    for (i = 1; i < numVer + 1; i++)
    {
        color[i] = 0;
    }
    for (i = 1; i < numVer + 1; i++)
    {
        // When the vertex is not explored
        if (color[i] == 0)
        {
            // Visit this vertex
            dfs_visit(i, graph, numVer, color, result);
        }
    }
}

// Find the largest element in an array
int largest(int arr[], int n)
{
    int i;
    int max = arr[1];
    for (i = 1; i < n + 1; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// Topological Sort
void topological_sort(AdjList *graph, int numVer)
{
    int *result, *sortedArray;
    if (graph == NULL)
    {
        printf("invalid graph\n");
        exit(EXIT_FAILURE);
    }
    // Allocate the memory
    result = (int *)malloc((numVer + 1) * sizeof(int));
    // DFS on the graph
    dfs(graph, numVer, result);
    // Print the result
    printf("The result from the topological sort is:\n");
    for (int i = numVer; i >= 1; i--)
    {
        printf("%d\t", result[i]); // print in console
    }
    // Free memory
    free(sortedArray);
    free(result);
}

int main(int argc, char *argv[])
{
    AdjList *graph = NULL;
    int numVertices;
    // Check input file
    if (argc < 2)
    {
        printf("too few arguments !");
        return 0;
    }
    clock_t begin = clock();                                 // Start timing
    graph = construct_adjlist(argv[1], graph, &numVertices); // Construct the adjacent list from input file
    topological_sort(graph, numVertices);
    clock_t end = clock();
    printf("\nTime taken = %lf\n", ((double)end - begin) / CLOCKS_PER_SEC); // print the time used
    return 0;
}