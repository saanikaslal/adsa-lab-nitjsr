#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

// Utility functions
int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node* node) {
    return node ? node->height : 0;
}

// Create a new node
struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotation
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get balance factor
int getBalance(struct Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Insert item
struct Node* insertItem(struct Node* node, int key) {
    if (!node) return createNode(key);

    if (key < node->key)
        node->left = insertItem(node->left, key);
    else if (key > node->key)
        node->right = insertItem(node->right, key);
    else
        return node; // Duplicate keys not allowed

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Balancing cases
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Find minimum value node
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

// Delete item
struct Node* deleteItem(struct Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        if (!root->left || !root->right) {
            struct Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balancing cases
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search item
int searchItem(struct Node* root, int key) {
    if (!root) return 0;
    if (key == root->key) return 1;
    if (key < root->key) return searchItem(root->left, key);
    return searchItem(root->right, key);
}

// Delete entire tree
void deleteTree(struct Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
    
}

// Create tree (initialization)
struct Node* createTree() {
    return NULL;
}

int main() {
    int keys[] ={30,20,40,10,25};
    int n =sizeof(keys)/sizeof(keys[0]);
    struct Node* root = createTree();
    printf("\n TREE CREATED--\n");

    for(int i=0; i<n ; i++)
        root = insertItem(root, keys[i]);

    printf("\n ITEMS INSERTED--\n");
    printf("Search 25: %s\n", searchItem(root, 25) ? "Found" : "Not Found");

    root = deleteItem(root, 20);
    printf("Search 20 after deletion: %s\n", searchItem(root, 20) ? "Found" : "Not Found");

    deleteTree(root);
    printf("\n--Tree Deleted--\n");
    return 0;
}
