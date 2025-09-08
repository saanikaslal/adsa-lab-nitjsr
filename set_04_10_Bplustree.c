#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 4  // Max number of children per internal node

typedef struct BPlusNode {
    bool is_leaf;
    int num_keys;
    int keys[ORDER - 1];
    struct BPlusNode* children[ORDER];
    struct BPlusNode* next;  // For leaf node linking
} BPlusNode;

// Create a new node
BPlusNode* createNode(bool is_leaf) {
    BPlusNode* node = (BPlusNode*)malloc(sizeof(BPlusNode));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->next = NULL;
    for (int i = 0; i < ORDER; i++) node->children[i] = NULL;
    return node;
}

// Create tree
BPlusNode* createTree() {
    return createNode(true);
}

// Search a key
bool searchItem(BPlusNode* root, int key) {
    while (!root->is_leaf) {
        int i = 0;
        while (i < root->num_keys && key >= root->keys[i]) i++;
        root = root->children[i];
    }
    for (int i = 0; i < root->num_keys; i++)
        if (root->keys[i] == key) return true;
    return false;
}

// Insert into leaf node
void insertIntoLeaf(BPlusNode* leaf, int key) {
    int i = leaf->num_keys - 1;
    while (i >= 0 && leaf->keys[i] > key) {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }
    leaf->keys[i + 1] = key;
    leaf->num_keys++;
}

// Insert item (simplified, no split)
void insertItem(BPlusNode* root, int key) {
    while (!root->is_leaf) {
        int i = 0;
        while (i < root->num_keys && key >= root->keys[i]) i++;
        root = root->children[i];
    }
    insertIntoLeaf(root, key);
}

// Delete item (simplified, no merge)
void deleteItem(BPlusNode* root, int key) {
    while (!root->is_leaf) {
        int i = 0;
        while (i < root->num_keys && key >= root->keys[i]) i++;
        root = root->children[i];
    }

    int i;
    for (i = 0; i < root->num_keys; i++) {
        if (root->keys[i] == key) break;
    }
    if (i == root->num_keys) return;

    for (; i < root->num_keys - 1; i++)
        root->keys[i] = root->keys[i + 1];
    root->num_keys--;
}

// Delete entire tree
void deleteTree(BPlusNode* root) {
    if (!root) return;
    if (!root->is_leaf) {
        for (int i = 0; i <= root->num_keys; i++)
            deleteTree(root->children[i]);
    }
    free(root);
}

// Display tree (in-order)
void display(BPlusNode* root) {
    if (!root) return;
    if (root->is_leaf) {
        for (int i = 0; i < root->num_keys; i++)
            printf("%d ", root->keys[i]);
    } else {
        for (int i = 0; i < root->num_keys; i++) {
            display(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        display(root->children[root->num_keys]);
    }
}

// Driver code
int main() {
     int items[] ={10,20,5,6,12,30,7,17};
    int n = sizeof(items)/sizeof(items[0]);
    BPlusNode* root = createTree();
     printf("\n--TREE CREATED--\n");

    for(int i=0; i<n;i++)
        insertItem(root, items[i]);
        
     printf("\n--VALUES INSERTED--\n");

    printf("Tree contents: ");
    display(root);
    printf("\n");

    printf("Search 15: %s\n", searchItem(root, 15) ? "Found" : "Not Found");

    deleteItem(root, 15);
    printf("Search 15 after deletion: %s\n", searchItem(root, 15) ? "Found" : "Not Found");

    deleteTree(root);
     printf("\n--TREE DELETED--\n");
    return 0;
}
