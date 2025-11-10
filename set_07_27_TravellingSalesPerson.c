#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 20
#define INF 100000000

int n;
int dist[MAX][MAX];
int dp[1 << MAX][MAX];

int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1)
        return dist[pos][0];

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            if (newAns < ans)
                ans = newAns;
        }
    }
    return dp[mask][pos] = ans;
}

void generateRandomGraph(int size) {
    n = size;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = (i == j) ? 0 : rand() % 100 + 1;
}

int main() {
    int sizes[] = {10, 12, 14, 16, 18};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Nodes\tTime (seconds)\n");
    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];
        generateRandomGraph(size);
        for (int i = 0; i < (1 << size); i++)
            for (int j = 0; j < size; j++)
                dp[i][j] = -1;

        clock_t start = clock();
        tsp(1, 0);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d\t%.4f\n", size, time_taken);
    }
    return 0;
}
