#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int u, v, weight;
} Edge;

int parent[MAX];

// Find root of a set
int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// Union of two sets
void unionSet(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

// Sort edges by weight (Bubble Sort for simplicity)
void sortEdges(Edge edges[], int E) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void kruskal(Edge edges[], int V, int E) {
    Edge result[MAX];
    int e = 0; // index for result[]
    int i = 0; // index for sorted edges

    for (int v = 0; v < V; v++)
        parent[v] = v;

    sortEdges(edges, E);

    while (e < V - 1 && i < E) {
        Edge next = edges[i++];
        int x = find(next.u);
        int y = find(next.v);

        if (x != y) {
            result[e++] = next;
            unionSet(x, y);
        }
    }

    int totalWeight = 0;
    printf("Edge \tWeight\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d\t%d\n", result[i].u, result[i].v, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total weight of MST: %d\n", totalWeight);
}

int main() {
    int V, E;
    Edge edges[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter each edge as: u v weight\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    kruskal(edges, V, E);

    return 0;
}
