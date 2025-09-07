#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int q1[SIZE], q2[SIZE];
int front1 = -1, rear1 = -1;
int front2 = -1, rear2 = -1;

// Queue operations
void enqueue1(int val) { q1[++rear1] = val; if (front1 == -1) front1 = 0; }
int dequeue1() { return q1[front1++]; }
int isEmpty1() { return front1 > rear1 || front1 == -1; }

void enqueue2(int val) { q2[++rear2] = val; if (front2 == -1) front2 = 0; }
int dequeue2() { return q2[front2++]; }
int isEmpty2() { return front2 > rear2 || front2 == -1; }

void swapQueues() {
    int tempQ[SIZE], tempFront, tempRear;
    for (int i = front2; i <= rear2; i++) tempQ[i] = q2[i];
    tempFront = front2; tempRear = rear2;

    for (int i = front1; i <= rear1; i++) q2[i] = q1[i];
    front2 = front1; rear2 = rear1;

    for (int i = tempFront; i <= tempRear; i++) q1[i] = tempQ[i];
    front1 = tempFront; rear1 = tempRear;
}

// Push: costly enqueue
void push(int val) {
    enqueue2(val);
    while (!isEmpty1()) {
        enqueue2(dequeue1());
    }
    swapQueues();
    printf("Pushed %d\n", val);
}

// Pop: efficient dequeue
void pop() {
    if (isEmpty1()) {
        printf("Stack Underflow!\n");
        return;
    }
    int val = dequeue1();
    printf("Popped %d\n", val);
}

// Display stack
void display() {
    if (isEmpty1()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack contents (top to bottom): ");
    for (int i = front1; i <= rear1; i++) {
        printf("%d ", q1[i]);
    }
    printf("\n");
}
int qa[SIZE], qb[SIZE];
int fa = -1, ra = -1;
int fb = -1, rb = -1;

void enqa(int val) { qa[++ra] = val; if (fa == -1) fa = 0; }
int deqa() { return qa[fa++]; }
int isemptya() { return fa > ra || fa == -1; }

void enqb(int val) { qb[++rb] = val; if (fb == -1) fb = 0; }
int deqb() { return qb[fb++]; }
int isemptyb() { return fb > rb || fb == -1; }

void swapAB() {
    for (int i = fb; i <= rb; i++) qa[i] = qb[i];
    fa = fb; ra = rb;
    fb = rb = -1;
}

// Push: efficient enqueue
void push2(int val) {
    enqa(val);
    printf("Pushed %d\n", val);
}

// Pop: costly dequeue
void pop2() {
    if (isemptya()) {
        printf("Stack Underflow!\n");
        return;
    }
    while (fa < ra) {
        enqb(deqa());
    }
    int val = deqa(); // last element
    swapAB();
    printf("Popped %d\n", val);
}

// Display stack
void display2() {
    if (isemptya()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack contents (top to bottom): ");
    for (int i = fa; i <= ra; i++) {
        printf("%d ", qa[i]);
    }
    printf("\n");
}
int main() {
    printf("Method 1 (Costly EnQueue):\n");
    push(10);
    push(20);
    push(30);
    display();
    pop();
    display();

    printf("\nMethod 2 (Costly DeQueue):\n");
    push2(100);
    push2(200);
    push2(300);
    display2();
    pop2();
    display2();

    return 0;
}
