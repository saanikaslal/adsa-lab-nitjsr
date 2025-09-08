#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

struct Node {
    int data;
    enum Color color;
    struct Node *left, *right, *parent;
};

// Utility function to create a new node
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

// Left rotate
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right rotate
void rightRotate(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) *root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Fix violations after insertion
void fixInsert(struct Node** root, struct Node* z) {
    while (z->parent && z->parent->color == RED) {
        struct Node* gp = z->parent->parent;
        if (z->parent == gp->left) {
            struct Node* y = gp->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                rightRotate(root, gp);
            }
        } else {
            struct Node* y = gp->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                leftRotate(root, gp);
            }
        }
    }
    (*root)->color = BLACK;
}

// Insert item
void insertItem(struct Node** root, int data) {
    struct Node* z = createNode(data);
    struct Node* y = NULL;
    struct Node* x = *root;

    while (x) {
        y = x;
        if (z->data < x->data) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (!y) *root = z;
    else if (z->data < y->data) y->left = z;
    else y->right = z;

    fixInsert(root, z);
}

// Search item
int searchItem(struct Node* root, int data) {
    while (root) {
        if (data == root->data) return 1;
        root = (data < root->data) ? root->left : root->right;
    }
    return 0;
}

// Delete tree
void deleteTree(struct Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Create tree
struct Node* createTree() {
    return NULL;
}

// In-order traversal for testing
void inorder(struct Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
    inorder(root->right);
}

int main() {
    int items[] ={10,20,30,15};
    int n = sizeof(items)/sizeof(items[0]);
    struct Node* root = createTree();
    printf("\n--TREE CREATED--\n");
    for(int i=0; i<n ; i++)
        insertItem(&root, items[i]);
    printf("\n--VALUES INSERTED--\n");
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Search 15: %s\n", searchItem(root, 15) ? "Found" : "Not Found");

    deleteTree(root);
    printf("\n--TREE DELETED--\n");
    return 0;
}
