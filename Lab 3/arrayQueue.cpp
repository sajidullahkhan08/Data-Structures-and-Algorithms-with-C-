#include <iostream>
using namespace std;

class Queue {
private:
    int front;
    int rear;
    int arr[5]; // fixed-size static array

public:
    Queue() {
        front = -1;
        rear = -1;
        for (int i = 0; i < 5; i++) {
            arr[i] = 0;
        }
    }

    bool isEmpty() {
        return front == -1 && rear == -1;
    }

    bool isFull() {
        return rear == 4;
    }

    void enqueue(int val) {
        if (isFull()) {
            cout << "Queue is Full (Overflow)!" << endl;
            return;
        } else if (isEmpty()) {
            // First element being inserted
            front = rear = 0;
        } else {
            // Move rear forward
            rear++;
        }
        arr[rear] = val;
        cout << val << " enqueued into the queue." << endl;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is Empty (Underflow)!" << endl;
            return -1;
        }
        int removed = arr[front];
        arr[front] = 0;

        if (front == rear) {
            // Last element being removed
            front = rear = -1;
        } else {
            // Move front forward
            front++;
        }
        return removed;
    }

    void display() {
        cout << "Queue elements: ";
        for (int i = 0; i < 5; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Queue q;
    int option, value;

    do {
        cout << "\nChoose an operation (Enter 0 to Exit):" << endl;
        cout << "1. Enqueue()\n2. Dequeue()\n3. isEmpty()\n4. isFull()\n5. Display()\n";
        cin >> option;

        switch(option) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                q.enqueue(value);
                break;
            case 2:
                cout << "Dequeued value: " << q.dequeue() << endl;
                break;
            case 3:
                cout << (q.isEmpty() ? "Queue is empty." : "Queue is not empty.") << endl;
                break;
            case 4:
                cout << (q.isFull() ? "Queue is full." : "Queue is not full.") << endl;
                break;
            case 5:
                q.display();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    } while (option != 0);

    return 0;
}
