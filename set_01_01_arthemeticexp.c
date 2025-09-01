#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX 200

int add(int a , int b){
    return a+b;
}

int sub(int a , int b){
    return a-b;
}

int div(int a , int b){
    return a/b;
}
int mul(int a , int b){
    return a*b;
}

#include <stdio.h>
#include <ctype.h>   // for isdigit()
#include <string.h>  // for strlen()

#define MAX 100

// Stack for operators
char stack[MAX];
int top = -1;

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

char pop() {
    if (top >= 0) {
        return stack[top--];
        return 
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

// Check precedence of operators
int precedence(char op) {
    switch (op) {
        case '/': return 3;
        case '*': return 3;
        case '+': return 2;
        case '-': return 2;
        default: return 0;
    }
}

// Convert infix to postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    char c;
    
    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];

        // If operand, add to postfix
        if (isdigit(c)) {
            postfix[k++] = c;
        }
        // If '(', push to stack
        else if (c == '(') {
            push(c);
        }
        // If ')', pop until '('
        else if (c == ')') {
            while (top != -1 && peek() != '(') {
                postfix[k++] = pop();
            }
            pop(); // remove '('
        }
        // If operator
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (top != -1 && precedence(peek()) >= precedence(c)) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    // Pop remaining operators
    while (top != -1) {
        postfix[k++] = pop();
    }

    postfix[k] = '\0'; // Null terminate
}

int main() {
    char infix[MAX], postfix[MAX],stack[MAX];
    char c;
    int val,ans=0;

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

   for(int i=0; postfix[i]!='\0'; i++){
    c = postfix[i];
    if(isdigit(c)){
        push(c);
    }
    else{
        switch(c){
            case '+':
            ans = popn(c) + popn(c);
            break;
            case '-':
            ans = popn(c) - popn(c);
            break;
            case '/':
            ans = popn(c) / popn(c);
            break;
            case '*':
            ans = popn(c) * popn(c);
            break;
            default:
            printf("Invalid");
            break;
        }
    }
   }

    return 0;
}
