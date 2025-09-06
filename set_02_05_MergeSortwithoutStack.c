#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Structure to represent a range
typedef struct {
    int left;
    int right;
} Range;

// Stack implementation
typedef struct {
    Range data[MAX];
    int top;
} Stack;

void push(Stack *s, int left, int right) {
    s->data[++(s->top)].left = left;
    s->data[s->top].right = right;
}

Range pop(Stack *s) {
    return s->data[(s->top)--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

// Merge function
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Non-recursive merge sort
void mergeSort(int arr[], int n) {
    Stack s;
    s.top = -1;

    // Step 1: Divide phase using stack
    push(&s, 0, n - 1);

    // Store all ranges to be merged later
    Range mergeRanges[MAX];
    int mergeCount = 0;

    while (!isEmpty(&s)) {
        Range r = pop(&s);
        int left = r.left;
        int right = r.right;

        if (left < right) {
            int mid = (left + right) / 2;

            // Push right and left halves
            push(&s, left, mid);
            push(&s, mid + 1, right);

            // Store merge task
            mergeRanges[mergeCount].left = left;
            mergeRanges[mergeCount].right = right;
            mergeCount++;
        }
    }

    // Step 2: Merge phase (reverse order)
    for (int i = mergeCount - 1; i >= 0; i--) {
        int left = mergeRanges[i].left;
        int right = mergeRanges[i].right;
        int mid = (left + right) / 2;
        merge(arr, left, mid, right);
    }
}

// Driver code
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    mergeSort(arr, n);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
