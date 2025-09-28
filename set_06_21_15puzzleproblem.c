#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 4
#define SIZE 16
#define MAX_STATES 100000   

typedef struct Node {
    int puzzle[N][N];
    int x, y; 
    int cost;
    int level;
    struct Node* parent;
} Node;

int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9,10,11,12},
    {13,14,15, 0}
};


int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};


int calculateCost(int puzzle[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (puzzle[i][j] && puzzle[i][j] != goal[i][j]) {
                int val = puzzle[i][j] - 1;
                cost += abs(i - val / N) + abs(j - val % N);
            }
    return cost;
}


char* puzzleToString(int puzzle[N][N]) {
    char* str = (char*)malloc(SIZE + 1);
    int k = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            str[k++] = puzzle[i][j] + 'A';
    str[k] = '\0';
    return str;
}


char* visited[MAX_STATES];
int visitedCount = 0;

int isVisited(int puzzle[N][N]) {
    char* key = puzzleToString(puzzle);
    for (int i = 0; i < visitedCount; i++) {
        if (strcmp(visited[i], key) == 0) {
            free(key);
            return 1;
        }
    }
    if (visitedCount < MAX_STATES) {
        visited[visitedCount++] = key; 
    } else {
        free(key);
    }
    return 0;
}


Node* createNode(int puzzle[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    memcpy(node->puzzle, puzzle, sizeof(node->puzzle));
    int temp = node->puzzle[x][y];
    node->puzzle[x][y] = node->puzzle[newX][newY];
    node->puzzle[newX][newY] = temp;
    node->x = newX;
    node->y = newY;
    node->level = level;
    node->cost = calculateCost(node->puzzle);
    node->parent = parent;
    return node;
}


int compare(const void* a, const void* b) {
    Node* n1 = *(Node**)a;
    Node* n2 = *(Node**)b;
    return (n1->cost + n1->level) - (n2->cost + n2->level);
}


void printPuzzle(int puzzle[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", puzzle[i][j]);
        printf("\n");
    }
    printf("\n");
}


void solve(int initial[N][N], int x, int y) {
    Node* root = createNode(initial, x, y, x, y, 0, NULL);
    Node* queue[100000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        qsort(queue + front, rear - front, sizeof(Node*), compare);
        Node* min = queue[front++];

        if (min->cost == 0) {
            printf("Solved in %d moves:\n", min->level);
            Node* temp = min;
            
            while (temp) {
                printPuzzle(temp->puzzle);
                temp = temp->parent;
            }
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = min->x + dx[i];
            int newY = min->y + dy[i];
            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Node* child = createNode(min->puzzle, min->x, min->y, newX, newY, min->level + 1, min);
                if (!isVisited(child->puzzle)) {
                    queue[rear++] = child;
                } else {
                    free(child);
                }
            }
        }
    }
}

int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9,10, 7,12},
        {13,14,11,15}
    };

    int x = 1, y = 2; 
    solve(initial, x, y);
    return 0;
}
