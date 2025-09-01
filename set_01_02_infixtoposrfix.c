#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

char stack[MAX];
int top = -1;

int preced(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}

// Push into stack
void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
    }
}

// Pop from stack
char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0';
}

// Peek top of stack
char peek() {
    if (top >= 0) {
        return stack[top];
    }
    return '\0';
}

void infixtopostfix(char infix[], char postfix[]) {
    int k = 0;
    char c;

    for (int i = 0; infix[i] != '\0'; i++) {
        c = infix[i];

        if (isalnum(c)) {  
            // if operand (number/variable), add to postfix
            postfix[k++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && peek() != '(') {
                postfix[k++] = pop();
            }
            pop(); // remove '('
        }
        else { // operator
            while (top != -1 && preced(peek()) >= preced(c)) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    // Pop all remaining operators
    while (top != -1) {
        postfix[k++] = pop();
    }

    postfix[k] = '\0'; // null-terminate
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter the Expression : ");
    scanf("%s", infix);

    infixtopostfix(infix, postfix);
    printf("\nThe postfix Expression : %s\n", postfix);

    return 0;
}
