#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int stack1[SIZE], stack2[SIZE];
int top1 = -1, top2 = -1;

// Stack operations
void push1(int val) { stack1[++top1] = val; }
int pop1() { return stack1[top1--]; }
void push2(int val) { stack2[++top2] = val; }
int pop2() { return stack2[top2--]; }
int isEmpty1() { return top1 == -1; }
int isEmpty2() { return top2 == -1; }
//Method-1
// Enqueue: costly push
void enqueue(int val) {
    while (!isEmpty1()) {
        push2(pop1());
    }
    push1(val);
    while (!isEmpty2()) {
        push1(pop2());
    }
    printf("Enqueued %d\n", val);
}

// Dequeue: efficient pop
void dequeue() {
    if (isEmpty1()) {
        printf("Queue Underflow!\n");
        return;
    }
    int val = pop1();
    printf("Dequeued %d\n", val);
}

// Display queue
void display() {
    if (isEmpty1()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue contents: ");
    for (int i = 0; i <= top1; i++) {
        printf("%d ", stack1[i]);
    }
    printf("\n");
}

//Method-2

// Reset stack pointers
int topA = -1, topB = -1;
int stackA[SIZE], stackB[SIZE];

void pushA(int val) { stackA[++topA] = val; }
int popA() { return stackA[topA--]; }
void pushB(int val) { stackB[++topB] = val; }
int popB() { return stackB[topB--]; }
int isEmptyA() { return topA == -1; }
int isEmptyB() { return topB == -1; }

// Enqueue: efficient push
void enqueue2(int val) {
    pushA(val);
    printf("Enqueued %d\n", val);
}

// Dequeue: costly pop
void dequeue2() {
    if (isEmptyA() && isEmptyB()) {
        printf("Queue Underflow!\n");
        return;
    }
    if (isEmptyB()) {
        while (!isEmptyA()) {
            pushB(popA());
        }
    }
    int val = popB();
    printf("Dequeued %d\n", val);
}

// Display queue
void display2() {
    if (isEmptyA() && isEmptyB()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue contents: ");
    for (int i = topB; i >= 0; i--) {
        printf("%d ", stackB[i]);
    }
    for (int i = 0; i <= topA; i++) {
        printf("%d ", stackA[i]);
    }
    printf("\n");
}

int main() {
    printf("Method-1 (Costly Push):\n");
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    dequeue();
    display();

    printf("\nMethod-2 (Costly Pop):\n");
    enqueue2(100);
    enqueue2(200);
    enqueue2(300);
    display2();
    dequeue2();
    display2();

    return 0;
}
