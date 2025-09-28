#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20  

int board[MAX];  

bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;  
        }
    }
    return true;
}


void solveNQueens(int row, int n) {
    if (row == n) {
        
        printf("Solution:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%c ", (board[i] == j) ? 'Q' : '.');
            }
            printf("\n");
        }
        printf("\n");
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            solveNQueens(row + 1, n);
            
        }
    }
}

int main() {
    int n;
    printf("Enter the number of queens (n): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid input. Please enter a value between 1 and %d.\n", MAX);
        return 1;
    }

    solveNQueens(0, n);
    return 0;
}
