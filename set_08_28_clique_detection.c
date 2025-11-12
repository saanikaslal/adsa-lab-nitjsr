#include <stdio.h>
#include <stdint.h>

#define MAXN 64

int n, e, m;
uint64_t adj[MAXN];
int found = 0;
int clique[MAXN], best[MAXN];
int best_size = 0;


int popcount(uint64_t x) {
    return __builtin_popcountll(x);
}


void search(int size, uint64_t candidates) {
    if (found) return;


    if (size + popcount(candidates) < m)
        return;

    if (size >= m) {
        for (int i = 0; i < size; i++)
            best[i] = clique[i];
        best_size = size;
        found = 1;
        return;
    }

    while (candidates) {
        int v = __builtin_ctzll(candidates);
        candidates &= ~(1ULL << v);

        clique[size] = v;
        search(size + 1, candidates & adj[v]);
    }
}

int main() {
    scanf("%d %d %d", &n, &e, &m);

    for (int i = 0; i < n; i++)
        adj[i] = 0;

    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        if (u != v) {
            adj[u] |= (1ULL << v);
            adj[v] |= (1ULL << u);
        }
    }

    uint64_t all = 0;
    for (int i = 0; i < n; i++) all |= (1ULL << i);

    search(0, all);

    if (found) {
        printf("Yes, clique of size %d exists.\n", m);
        printf("Clique vertices: ");
        for (int i = 0; i < best_size; i++)
            printf("%d ", best[i] + 1);
        printf("\n");
    } else {
        printf("No clique of size %d found.\n", m);
    }

    return 0;
}
