#include <stdio.h>
#include <stdlib.h>

// Function to sort individual buckets using Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Bucket Sort function
void bucketSort(int arr[], int n) {
    // Find maximum value to decide bucket ranges
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int bucketCount = 10; // number of buckets
    int bucketRange = (max / bucketCount) + 1;

    // Create buckets (array of arrays)
    int *buckets[bucketCount];
    int bucketSizes[bucketCount];

    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = (int *)malloc(n * sizeof(int));
        bucketSizes[i] = 0;
    }

    // Distribute array elements into buckets
    for (int i = 0; i < n; i++) {
        int index = arr[i] / bucketRange;
        buckets[index][bucketSizes[index]++] = arr[i];
    }

    // Sort individual buckets and concatenate
    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        if (bucketSizes[i] > 0) {
            insertionSort(buckets[i], bucketSizes[i]);
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[idx++] = buckets[i][j];
            }
        }
        free(buckets[i]); // free allocated memory
    }
}
int main(){
    int arr[50];
    int n;
    printf("Enter the size ");
    scanf("%d",&n);
    printf("Enter the Array ");
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);

    bucketSort(arr, n);

    printf("\n Sorted Array :");
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);

    return 0;
}

