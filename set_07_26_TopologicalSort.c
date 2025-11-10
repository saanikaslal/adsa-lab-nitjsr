#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int V, E;
int adj[MAX][MAX];
int visited[MAX];
int stack[MAX], top = -1;


void dfs(int v) {
    visited[v] = 1;
    for (int i = 0; i < V; i++) {
        if (adj[v][i] && !visited[i])
            dfs(i);
    }
    stack[++top] = v;
}


void topologicalSort() {
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    for (int i = 0; i < V; i++)
        if (!visited[i])
            dfs(i);

    printf("Topological Sort Order:\n");
    while (top != -1)
        printf("%d ", stack[top--]);
    printf("\n");
}


int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges (u v) for directed graph:\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
    }

    topologicalSort();
    return 0;
}
/*
Enter number of vertices: 6
Enter number of edges: 6
Enter edges (u v) for directed graph:
5 2
5 0
4 0
4 1
2 3
3 1
Topological Sort Order:
5 4 2 3 1 0*/