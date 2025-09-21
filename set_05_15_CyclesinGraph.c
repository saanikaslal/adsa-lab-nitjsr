#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int adj[MAX][MAX]; // adjacency matrix
int n, e;

int shortestCycle() {
    int minCycle = INT_MAX;

    for (int start = 0; start < n; start++) {
        int dist[MAX], parent[MAX];
        for (int i = 0; i < n; i++) {
            dist[i] = -1;
            parent[i] = -1;
        }

        dist[start] = 0;

        int queue[MAX], front = 0, rear = 0;
        queue[rear++] = start;

        while (front < rear) {
            int u = queue[front++];
            for (int v = 0; v < n; v++) {
                if (adj[u][v]) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        parent[v] = u;
                        queue[rear++] = v;
                    }
                    // Found a cycle (ignore immediate parent)
                    else if (parent[u] != v) {
                        int cycleLen = dist[u] + dist[v] + 1;
                        if (cycleLen < minCycle) {
                            minCycle = cycleLen;
                        }
                    }
                }
            }
        }
    }
    return (minCycle == INT_MAX ? -1 : minCycle);
}


int visited[MAX];
int maxCycle = 0;

void DFS(int u, int parent, int depth) {
    visited[u] = depth;

    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                DFS(v, u, depth + 1);
            }
            else if (v != parent) {
                // Found a cycle
                int cycleLen = abs(visited[u] - visited[v]) + 1;
                if (cycleLen > maxCycle) {
                    maxCycle = cycleLen;
                }
            }
        }
    }
}

int longestCycle() {
    for (int i = 0; i < n; i++) visited[i] = 0;
    maxCycle = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS(i, -1, 1);
        }
    }
    return (maxCycle == 0 ? -1 : maxCycle);
}


int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1; // undirected graph
    }

    int small = shortestCycle();
    int large = longestCycle();

    printf("\nSmallest cycle length = ");
    if (small == -1) printf("No cycle found\n");
    else printf("%d\n", small);

    printf("Largest cycle length = ");
    if (large == -1) printf("No cycle found\n");
    else printf("%d\n", large);

    return 0;
}
