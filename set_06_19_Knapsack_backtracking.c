#include <stdio.h>

int maxValue = 0; 


void knapsackBacktrack(int i, int n, int W, int wt[], int val[], int currWeight, int currValue) {
  
    if (i == n) {
        if (currWeight <= W && currValue > maxValue)
            maxValue = currValue;
        return;
    }

 
    if (currWeight + wt[i] <= W)
        knapsackBacktrack(i + 1, n, W, wt, val, currWeight + wt[i], currValue + val[i]);

   
    knapsackBacktrack(i + 1, n, W, wt, val, currWeight, currValue);
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);

    int wt[n], val[n];

    printf("Enter weights of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &wt[i]);

    printf("Enter values of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);

    printf("Enter capacity of knapsack: ");
    scanf("%d", &W);

   
    knapsackBacktrack(0, n, W, wt, val, 0, 0);

    printf("Maximum value in knapsack = %d\n", maxValue);

    return 0;
}
