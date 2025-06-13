#include <iostream>
using namespace std;

class Queue {
    public:
        int QArray[10];
        int front, rear;

        Queue() {
            front = -1;
            rear = -1; // Corrected: Initialize rear to -1 as well
            for(int i = 0; i < 10; i++) {
                QArray[i] = 0; // Initialize the array elements to 0
            }
        }

        bool isEmpty() {
            return (front == -1); // Simplified: Queue is empty if front is -1
        }

        bool isFull() {
            return ((rear + 1) % 10 == front); // Corrected: Circular queue full condition
        }

        void enqueue(int value) {
            if (isFull()) {
                cout << "The Queue is Full!" << endl;
                return;
            }
            if (isEmpty()) {
                front = 0;
            }
            rear = (rear + 1) % 10; // Corrected: Circular increment
            QArray[rear] = value;
            cout << "Item " << value << " is enqueued!" << endl;
        }

        int dequeue() {
            if (isEmpty()) {
                cout << "The Queue is already empty!" << endl;
                return -1;
            }
            int removed = QArray[front];
            if (front == rear) {
                front = -1;
                rear = -1; // Corrected: Reset both front and rear when queue becomes empty
            } else {
                front = (front + 1) % 10; // Corrected: Circular increment
            }
            return removed;
        }

        void display() {
            if (isEmpty()) {
                cout << "Queue is empty." << endl;
                return;
            }
            int i = front;
            do {
                cout << QArray[i] << " ";
                i = (i + 1) % 10; // Corrected: Circular increment
            } while (i != (rear + 1) % 10); // Corrected: Iterate until we reach the rear
            cout << endl;
        }
};

int main() {
    Queue Q;

    Q.enqueue(1);
    Q.enqueue(2);
    Q.enqueue(3);
    Q.enqueue(4);

    cout << "The dequeued item is: " << Q.dequeue() << endl;

    Q.display();

    Q.enqueue(5);
    Q.enqueue(6);
    Q.display();
}
