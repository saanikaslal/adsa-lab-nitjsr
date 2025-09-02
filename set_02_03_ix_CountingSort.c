#include <stdio.h>
#include <string.h>  // for memset

// Function to get the maximum element in the array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// Counting Sort function
void countingSort(int arr[], int n) {
    int max = getMax(arr, n);

    // Create count array to store frequency of each number
    int count[max + 1];
    memset(count, 0, sizeof(count));  // initialize with 0

    // Store counts
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // Change count[i] so that count[i] now contains actual position
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // Build output array (stable sorting)
    int output[n];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy output back to arr
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}


// Driver code
int main(){
    int arr[50];
    int n;
    printf("Enter the size ");
    scanf("%d",&n);
    printf("Enter the Array ");
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);

    countingSort(arr, n);

    printf("\n Sorted Array :");
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);

    return 0;
}
