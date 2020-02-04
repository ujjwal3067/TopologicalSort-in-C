#ifndef _TOPLOGICAL_SORT_H_
#define _TOPLOGICAL_SORT_H_

// Define the basic component in adjacent list
typedef struct adjacent_list
{
    int vertex;                 // The vertex number
    struct adjacent_list *next; // Its child
} * AdjList, *AdjListNodePtr, AdjListNode;

// Fcuntion used
AdjList insert_vertex(AdjList adjList, int vertex);
AdjList *construct_adjlist(const char *filename, AdjList *adjList, int *pnumVertices);
void dfs_visit(int i, AdjList *graph, int numVer, int *color, int *result);
void dfs(AdjList *graph, int numVer, int *result);
void array_swap(int A[], int m, int n);
int largest(int arr[], int n);
void topological_sort(AdjList *graph, int numVertices);

#endif