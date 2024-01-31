#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define V 2000

void printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}

void bellmanFord(int **graph, int src)
{
    int *dist = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        for (int u = 0; u < V; u++)
        {
            for (int v = 0; v < V; v++)
            {
                if (graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                fprintf(stderr, "Graph contains negative weight cycle.\n");
                free(dist);
                return;
            }
        }
    }

    printSolution(dist);

    free(dist);
}

int **readGraphFromFile(const char *filename)
{
    int **graph = (int **)malloc(5000 * sizeof(int *));
    for (int i = 0; i < 5000; i++)
        graph[i] = (int *)malloc(5000 * sizeof(int));

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < 5000; i++)
    {
        for (int j = 0; j < 5000; j++)
        {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);

    return graph;
}

int main()
{
    const char *filename = "graph.txt";
    int **graph = readGraphFromFile(filename);

    printf("\nBellman-Ford Algorithm:\n");
    bellmanFord(graph, 0);

    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}