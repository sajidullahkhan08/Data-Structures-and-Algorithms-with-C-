#include <iostream>
using namespace std;

#define SIZE 100

struct Deque {
    int arr[SIZE];
    int front = -1;
    int rear = -1;
};

bool isFull(Deque dq) {
    return ((dq.front == 0 && dq.rear == SIZE - 1) || (dq.front == dq.rear + 1));
}

bool isEmpty(Deque dq) {
    return dq.front == -1;
}

void insertFront(Deque &dq, int val) {
    if (isFull(dq)) {
        cout << "Deque Overflow\n";
        return;
    }

    if (isEmpty(dq)) dq.front = dq.rear = 0;
    else if (dq.front == 0) dq.front = SIZE - 1;
    else dq.front--;

    dq.arr[dq.front] = val;
}

void insertRear(Deque &dq, int val) {
    if (isFull(dq)) {
        cout << "Deque Overflow\n";
        return;
    }

    if (isEmpty(dq)) dq.front = dq.rear = 0;
    else if (dq.rear == SIZE - 1) dq.rear = 0;
    else dq.rear++;

    dq.arr[dq.rear] = val;
}

void deleteFront(Deque &dq) {
    if (isEmpty(dq)) {
        cout << "Deque Underflow\n";
        return;
    }

    if (dq.front == dq.rear) dq.front = dq.rear = -1;
    else if (dq.front == SIZE - 1) dq.front = 0;
    else dq.front++;
}

void deleteRear(Deque &dq) {
    if (isEmpty(dq)) {
        cout << "Deque Underflow\n";
        return;
    }

    if (dq.front == dq.rear) dq.front = dq.rear = -1;
    else if (dq.rear == 0) dq.rear = SIZE - 1;
    else dq.rear--;
}

void printDeque(Deque dq) {
    if (isEmpty(dq)) {
        cout << "Deque is empty\n";
        return;
    }

    int i = dq.front;
    while (true) {
        cout << dq.arr[i] << " ";
        if (i == dq.rear) break;
        i = (i + 1) % SIZE;
    }
    cout << "\n";
}

int main() {
    Deque dq;

    insertRear(dq, 10);
    insertRear(dq, 20);
    insertFront(dq, 5);
    printDeque(dq);  // Output: 5 10 20

    deleteFront(dq);
    deleteRear(dq);
    printDeque(dq);  // Output: 10

    return 0;
}
