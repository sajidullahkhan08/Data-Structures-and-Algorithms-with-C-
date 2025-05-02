#include <iostream>
using namespace std;

const int MAX = 5;

class PriorityQueue {
private:
    int values[MAX];     // Stores the data
    int priorities[MAX]; // Stores the corresponding priorities
    int size;            // Current number of elements

public:
    PriorityQueue() {
        size = 0;
        for (int i = 0; i < MAX; i++) {
            values[i] = 0;
            priorities[i] = 0;
        }
    }

    bool isFull() {
        return size == MAX;
    }

    bool isEmpty() {
        return size == 0;
    }

    void enqueue(int val, int pri) {
        if (isFull()) {
            cout << "Priority Queue is Full!" << endl;
            return;
        }

        int i;

        // Shift lower-priority elements one step back to insert the new element at correct position
        for (i = size - 1; i >= 0 && priorities[i] < pri; i--) {
            values[i + 1] = values[i];
            priorities[i + 1] = priorities[i];
        }

        // Insert the new value at its correct sorted position
        values[i + 1] = val;
        priorities[i + 1] = pri;
        size++;

        cout << val << " enqueued with priority " << pri << "." << endl;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Priority Queue is Empty!" << endl;
            return;
        }

        cout << "Dequeued value: " << values[0] << " (Priority: " << priorities[0] << ")" << endl;

        // Shift everything to the left
        for (int i = 0; i < size - 1; i++) {
            values[i] = values[i + 1];
            priorities[i] = priorities[i + 1];
        }

        values[size - 1] = 0;
        priorities[size - 1] = 0;
        size--;
    }

    void peek() {
        if (isEmpty()) {
            cout << "Priority Queue is Empty!" << endl;
        } else {
            cout << "Front value: " << values[0] << " (Priority: " << priorities[0] << ")" << endl;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Priority Queue is Empty!" << endl;
            return;
        }

        cout << "Priority Queue (Highest Priority First):" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Value: " << values[i] << ", Priority: " << priorities[i] << endl;
        }
    }
};

int main() {
    PriorityQueue pq;
    int option, val, pri;

    do {
        cout << "\nChoose an operation (Enter 0 to Exit):" << endl;
        cout << "1. Enqueue()\n2. Dequeue()\n3. Peek()\n4. Display()\n";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> val;
                cout << "Enter priority (higher number = higher priority): ";
                cin >> pri;
                pq.enqueue(val, pri);
                break;
            case 2:
                pq.dequeue();
                break;
            case 3:
                pq.peek();
                break;
            case 4:
                pq.display();
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
