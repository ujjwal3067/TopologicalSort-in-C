# TopologicalSort-in-C

The algorithm used here to perform topological sort is DFS-based. First, run a depth first search on the input graph. We can get the time when the vertex is finished for each vertex. When the vertex is finished (i.e. when the finish time is updated in regular DFS), put the vertex in an array. When finished, the order in the array is the reversed topological order.
