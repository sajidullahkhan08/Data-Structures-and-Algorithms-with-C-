#include <iostream>
using namespace std;

class CircularQueue {
private:
    int front;
    int rear;
    int arr[5];
    int size;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
        size = 5;
        for (int i = 0; i < size; i++) {
            arr[i] = 0;
        }
    }

    bool isEmpty() {
        return front == -1 && rear == -1;
    }

    bool isFull() {
        // Queue is full when next position of rear is front
        if ((rear + 1 == front) || (front == 0 && rear == size - 1)) {
            return true;
        }
        return false;
    }

    void enqueue(int val) {
        if (isFull()) {
            cout << "Queue is Full (Overflow)!" << endl;
            return;
        }

        if (isEmpty()) {
            // First element is being inserted
            front = rear = 0;
        } else if (rear == size - 1 && front != 0) {
            // Wrap rear to 0 manually
            rear = 0;
        } else {
            rear++; // Move rear forward
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
            // Only one element was present
            front = rear = -1;
        } else if (front == size - 1) {
            // Wrap front to 0 manually
            front = 0;
        } else {
            front++; // Move front forward
        }

        return removed;
    }

    void display() {
        cout << "Queue elements: ";
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }

        if (rear >= front) {
            for (int i = front; i <= rear; i++) {
                cout << arr[i] << " ";
            }
        } else {
            for (int i = front; i < size; i++) {
                cout << arr[i] << " ";
            }
            for (int i = 0; i <= rear; i++) {
                cout << arr[i] << " ";
            }
        }
        cout << endl;
    }

    void showIndexes() {
        cout << "Front index: " << front << ", Rear index: " << rear << endl;
    }
};

int main() {
    CircularQueue cq;
    int option, value;

    do {
        cout << "\nChoose an operation (Enter 0 to Exit):" << endl;
        cout << "1. Enqueue()\n2. Dequeue()\n3. isEmpty()\n4. isFull()\n5. Display()\n6. Show Indexes\n";
        cin >> option;

        switch(option) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                cq.enqueue(value);
                break;
            case 2:
                cout << "Dequeued value: " << cq.dequeue() << endl;
                break;
            case 3:
                cout << (cq.isEmpty() ? "Queue is empty." : "Queue is not empty.") << endl;
                break;
            case 4:
                cout << (cq.isFull() ? "Queue is full." : "Queue is not full.") << endl;
                break;
            case 5:
                cq.display();
                break;
            case 6:
                cq.showIndexes();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    } while(option != 0);

    return 0;
}
