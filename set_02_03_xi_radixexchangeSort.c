#include <stdio.h>

// Function to swap two numbers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Radix Exchange Sort (Binary QuickSort)
void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0)
        return;

    int i = left, j = right;

    while (i <= j) {
        // Move i forward until the bit is 0
        while (i <= j && ((arr[i] >> bit) & 1) == 0)
            i++;

        // Move j backward until the bit is 1
        while (i <= j && ((arr[j] >> bit) & 1) == 1)
            j--;

        if (i < j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    // Recurse for two halves on next lower bit
    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}



// Find the position of the most significant bit (MSB)
int getMaxBit(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int bit = 0;
    while (max > 0) {
        bit++;
        max >>= 1;
    }
    return bit - 1;  // index of MSB
}

int main(){
    int arr[50];
    int n;
    printf("Enter the size ");
    scanf("%d",&n);
    printf("Enter the Array ");
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);

    int msb = getMaxBit(arr, n);  // find the MSB
    radixExchangeSort(arr, 0, n - 1, msb);

    printf("\n Sorted Array :");
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);

    return 0;
}


