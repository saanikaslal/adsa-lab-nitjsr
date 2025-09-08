#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 4  // Order of B-tree

typedef struct BTreeNode {
    int keys[M - 1];
    struct BTreeNode* children[M];
    int num_keys;
    bool is_leaf;
} BTreeNode;

// Create a new node
BTreeNode* createNode(bool is_leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    for (int i = 0; i < M; i++) node->children[i] = NULL;
    return node;
}

// Search a key
bool searchItem(BTreeNode* root, int key) {
    int i = 0;
    while (i < root->num_keys && key > root->keys[i]) i++;

    if (i < root->num_keys && key == root->keys[i]) return true;

    if (root->is_leaf) return false;

    return searchItem(root->children[i], key);
}

// Split child
void splitChild(BTreeNode* parent, int index) {
    BTreeNode* child = parent->children[index];
    BTreeNode* newNode = createNode(child->is_leaf);
    newNode->num_keys = M / 2 - 1;

    for (int i = 0; i < M / 2 - 1; i++)
        newNode->keys[i] = child->keys[i + M / 2];

    if (!child->is_leaf) {
        for (int i = 0; i < M / 2; i++)
            newNode->children[i] = child->children[i + M / 2];
    }

    child->num_keys = M / 2 - 1;

    for (int i = parent->num_keys; i > index; i--)
        parent->children[i + 1] = parent->children[i];

    parent->children[index + 1] = newNode;

    for (int i = parent->num_keys - 1; i >= index; i--)
        parent->keys[i + 1] = parent->keys[i];

    parent->keys[index] = child->keys[M / 2 - 1];
    parent->num_keys++;
}

// Insert non-full
void insertNonFull(BTreeNode* node, int key) {
    int i = node->num_keys - 1;

    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        while (i >= 0 && key < node->keys[i]) i--;

        if (node->children[i + 1]->num_keys == M - 1) {
            splitChild(node, i + 1);
            if (key > node->keys[i + 1]) i++;
        }
        insertNonFull(node->children[i + 1], key);
    }
}

// Insert item
void insertItem(BTreeNode** root, int key) {
    BTreeNode* r = *root;
    if (r->num_keys == M - 1) {
        BTreeNode* s = createNode(false);
        s->children[0] = r;
        splitChild(s, 0);
        insertNonFull(s, key);
        *root = s;
    } else {
        insertNonFull(r, key);
    }
}

// Delete tree
void deleteTree(BTreeNode* root) {
    if (!root) return;
    if (!root->is_leaf) {
        for (int i = 0; i <= root->num_keys; i++)
            deleteTree(root->children[i]);
    }
    free(root);
}

// Create tree
BTreeNode* createTree() {
    return createNode(true);
}

// Display (in-order)
void display(BTreeNode* root) {
    if (!root) return;
    for (int i = 0; i < root->num_keys; i++) {
        if (!root->is_leaf) display(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->is_leaf) display(root->children[root->num_keys]);
}


int main() {
    int items[] ={10,20,5,6,12,30,7,17};
    int n = sizeof(items)/sizeof(items[0]);
    BTreeNode* root = createTree();
    printf("\n--TREE CREATED--\n");
    for(int i=0;i<n;i++)
        insertItem(&root, items[i]);
    

    printf("\n--ITEMS INSERTED--\n");

    printf("B-Tree contents: ");
    display(root);
    printf("\n");

    printf("Search 6: %s\n", searchItem(root, 6) ? "Found" : "Not Found");

    deleteTree(root);
    printf("\n--TREE DELETED--\n");
    return 0;
}
