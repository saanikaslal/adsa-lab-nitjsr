#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Graph stored as adjacency list
int adj[MAX][MAX];
int n; // number of vertices

int color[MAX]; // 0=white, 1=gray, 2=black
int d[MAX], f[MAX], time = 0;

// Add edge (directed graph)
void addEdge(int u, int v) {
    adj[u][v] = 1;
}

// DFS Visit function
void DFS_Visit(int u) {
    color[u] = 1; // gray
    d[u] = ++time;

    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (color[v] == 0) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFS_Visit(v);
            }
            else if (color[v] == 1) {
                printf("Back Edge: %d -> %d\n", u, v);
            }
            else if (d[u] < d[v]) {
                printf("Forward Edge: %d -> %d\n", u, v);
            }
            else {
                printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }

    color[u] = 2; // black
    f[u] = ++time;
}

// DFS main
void DFS() {
    for (int i = 0; i < n; i++) {
        color[i] = 0; // white
        d[i] = f[i] = 0;
    }
    time = 0;

    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            DFS_Visit(i);
        }
    }
}

int main() {
    int e, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    printf("\nDFS Edge Classification:\n");
    DFS();

    printf("\nDiscovery and Finish Times:\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: d=%d, f=%d\n", i, d[i], f[i]);
    }

    return 0;
}
