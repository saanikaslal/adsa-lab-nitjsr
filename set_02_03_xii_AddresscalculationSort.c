#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list (to handle collisions)
struct Node {
    int data;
    struct Node* next;
};

// Insert element into sorted linked list (keeps bucket sorted)
void insertSorted(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL || (*head)->data >= value) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL && current->next->data < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Address Calculation Sort function
void addressCalculationSort(int arr[], int n) {
    // Find max element to decide address function range
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int bucketCount = n;  // one bucket per element (can be tuned)

    // Create bucket array (array of linked lists)
    struct Node* buckets[bucketCount];
    for (int i = 0; i < bucketCount; i++)
        buckets[i] = NULL;

    // Address function: map value to bucket index
    for (int i = 0; i < n; i++) {
        int index = (arr[i] * bucketCount) / (max + 1); // scale value into [0, bucketCount-1]
        insertSorted(&buckets[index], arr[i]);
    }

    // Collect numbers from buckets back to array
    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        struct Node* current = buckets[i];
        while (current != NULL) {
            arr[idx++] = current->data;
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// Utility function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver code
int main() {
    int arr[] = {42, 32, 33, 52, 37, 47, 51};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    addressCalculationSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}
