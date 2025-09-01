#include<stdio.h>
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp (1 = units, 10 = tens, etc.)
void countSort(int arr[], int n, int exp) {
    int output[n]; // output array
    int count[10] = {0};

    // Count occurrences of each digit
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that it contains actual position of this digit
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build output array (stable sort)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy output[] to arr[]
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to implement Radix Sort
void radixSort(int arr[], int n) {
    int m = getMax(arr, n);

    // Do counting sort for every digit (exp = 1, 10, 100, ...)
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main(){
    int arr[50];
    int n;
    printf("Enter the size ");
    scanf("%d",&n);
    printf("Enter the Array ");
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);

    radixSort(arr,n);

    printf("\n Sorted Array :");
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);

    return 0;
}