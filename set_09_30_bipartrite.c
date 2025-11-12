#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];
int color[MAX];
int n;

int isBipartite(int start) {
    int queue[MAX], front = 0, rear = 0;

    queue[rear++] = start;
    color[start] = 1; 

    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < n; v++) {
            if (graph[u][v]) {
                if (color[v] == color[u])
                    return 0;

                if (color[v] == 0) {
                    color[v] = -color[u];
                    queue[rear++] = v;
                }
            }
        }
    }
    return 1;
}

int main() {
    int e, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        color[i] = 0;
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v) 0-indexed:\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (color[i] == 0) { 
            if (!isBipartite(i)) {
                printf("Graph is NOT bipartite.\n");
                return 0;
            }
        }
    }

    printf("Graph IS bipartite.\n");
    return 0;
}
