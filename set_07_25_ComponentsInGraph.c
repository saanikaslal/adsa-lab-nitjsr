#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int V; 
int adj[MAX][MAX], transpose[MAX][MAX];


int visited[MAX], stack[MAX], top = -1;

void dfs1(int v) {
    visited[v] = 1;
    for (int i = 0; i < V; i++)
        if (adj[v][i] && !visited[i])
            dfs1(i);
    stack[++top] = v;
}

void dfs2(int v) {
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < V; i++)
        if (transpose[v][i] && !visited[i])
            dfs2(i);
}

void findSCCs() {
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < V; i++)
        if (!visited[i]) dfs1(i);

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            transpose[i][j] = adj[j][i];

    memset(visited, 0, sizeof(visited));
    printf("Strongly Connected Components:\n");
    while (top != -1) {
        int v = stack[top--];
        if (!visited[v]) {
            dfs2(v);
            printf("\n");
        }
    }
}


int disc[MAX], low[MAX], parent[MAX], ap[MAX];
int time = 0;

void APBridgeUtil(int u) {
    visited[u] = 1;
    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v = 0; v < V; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                APBridgeUtil(v);
                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u]))
                    ap[u] = 1;

                if (low[v] > disc[u])
                    printf("Bridge: %d - %d\n", u, v);
            } else if (v != parent[u])
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

void findArticulationPointsAndBridges() {
    memset(visited, 0, sizeof(visited));
    memset(disc, -1, sizeof(disc));
    memset(low, -1, sizeof(low));
    memset(parent, -1, sizeof(parent));
    memset(ap, 0, sizeof(ap));

    printf("Articulation Points:\n");
    for (int i = 0; i < V; i++)
        if (!visited[i])
            APBridgeUtil(i);

    for (int i = 0; i < V; i++)
        if (ap[i]) printf("%d ", i);
    printf("\n");
}

int bccStack[MAX][2], bccTop = -1;

void BCCUtil(int u) {
    visited[u] = 1;
    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v = 0; v < V; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                bccStack[++bccTop][0] = u;
                bccStack[bccTop][1] = v;
                BCCUtil(v);
                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u])) {
                    printf("Biconnected Component:\n");
                    while (bccStack[bccTop][0] != u || bccStack[bccTop][1] != v)
                        printf("%d-%d\n", bccStack[bccTop][0], bccStack[bccTop--][1]);
                    printf("%d-%d\n", bccStack[bccTop][0], bccStack[bccTop--][1]);
                }
            } else if (v != parent[u] && disc[v] < disc[u]) {
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
                bccStack[++bccTop][0] = u;
                bccStack[bccTop][1] = v;
            }
        }
    }
}

void findBCCs() {
    memset(visited, 0, sizeof(visited));
    memset(disc, -1, sizeof(disc));
    memset(low, -1, sizeof(low));
    memset(parent, -1, sizeof(parent));
    bccTop = -1;
    time = 0;

    for (int i = 0; i < V; i++)
        if (!visited[i])
            BCCUtil(i);
}

void addEdge(int u, int v, int directed) {
    adj[u][v] = 1;
    if (!directed) adj[v][u] = 1;
}

int main() {
    V = 5;
    memset(adj, 0, sizeof(adj));

    addEdge(0, 1, 0);
    addEdge(1, 3, 0);
    addEdge(3, 2, 0);
    addEdge(2, 0, 0);
    addEdge(3, 4, 0);

    findSCCs();
    findArticulationPointsAndBridges();
    findBCCs();

    return 0;
}
