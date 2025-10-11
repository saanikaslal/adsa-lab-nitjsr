#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100


typedef struct {
    char id[10];
    int deadline;
    int profit;
} Job;


int compare(const void *a, const void *b) {
    return ((Job *)b)->profit - ((Job *)a)->profit;
}


void jobSequencing(Job jobs[], int n) {

    qsort(jobs, n, sizeof(Job), compare);


    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }


    char schedule[maxDeadline + 1][10]; 
    int slot[maxDeadline + 1];
    for (int i = 0; i <= maxDeadline; i++)
        slot[i] = 0;

    int totalProfit = 0;


    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) {
                slot[j] = 1;
                strcpy(schedule[j], jobs[i].id);
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }


    printf("Scheduled Jobs: ");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i])
            printf("%s ", schedule[i]);
    }
    printf("\nTotal Profit: %d\n", totalProfit);
}


int main() {
    Job jobs[] = {
        {"J1", 2, 60},
        {"J2", 1, 100},
        {"J3", 3, 20},
        {"J4", 2, 40},
        {"J5", 1, 20}
    };
    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobSequencing(jobs, n);
    return 0;
}
