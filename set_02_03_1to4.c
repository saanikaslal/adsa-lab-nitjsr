#include<stdio.h>
#include<string.h>

void bubblesort(int a[],int n){
    for(int i = 0; i<n ; i++)
        for(int j=0; j<n-i-1;j++)
            if(a[j]>=a[j+1]){
                int temp = a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
}

void insertionsort(int a[], int n) {
    for (int i = 1; i < n; i++) {   // first element at a[0] considered sorted
        int key = a[i];
        int j = i - 1;

        // Move elements greater than key to one position ahead
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        // Insert the key at correct position
        a[j + 1] = key;
    }
}

void selectionsort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;  // Assume the first element of unsorted part is minimum

        // Find the index of the minimum element in the unsorted part
            for (int j = i + 1; j < n; j++)
                if (a[j] < a[minIndex])
                    minIndex = j;

        // Swap the found minimum element with the first element of unsorted part
        if (minIndex != i) {
            int temp = a[i];
            a[i] = a[minIndex];
            a[minIndex] = temp;
        }
    }
}

void shellsort(int a[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];
            a[j] = temp;
        }
    }

}



void display(int a[],int n){
    for(int i=0; i<n; i++)
        printf("%d ",a[i]);
}

void copySortDisplay(int dest[], int src[], int n, void (*sortFunc)(int[], int), const char *name) {
    // Copy the original array
    for(int i=0; i<n; i++)
        dest[i] = src[i];

    // Sort using the passed function
    sortFunc(dest, n);

    // Display
    printf("%s Sorted Array: ", name);
    display(dest, n);
    printf("\n");
}

void main(){
    int n, a[50],temp[50];
    printf("Enter the Size ");
    scanf("%d",&n);
    printf("\n Enter %d Values \n",n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    // Make copies for each sort
    int arrBubble[50], arrInsertion[50], arrSelection[50],arrShell[50];
    int arrquick[50], arrmerge[50];

copySortDisplay(arrInsertion, a, n, insertionsort, "Insertion");
copySortDisplay(arrBubble, a, n, bubblesort, "Bubble");
copySortDisplay(arrSelection, a, n, selectionsort, "Selection");
copySortDisplay(arrShell, a, n, shellsort, "Shell");
//copySortDisplay(arrquick, a, n, quicksort, "Selection");
//copySortDisplay(arrmerge, a, n, mergesort, "Shell");

}