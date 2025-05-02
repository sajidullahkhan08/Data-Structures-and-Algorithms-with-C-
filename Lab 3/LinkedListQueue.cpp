#include <iostream>
using namespace std;

// Node class represents each element in the queue
class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = rear = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            // First element in the queue
            front = rear = newNode;
        } else {
            // Add new node at the rear
            rear->next = newNode;
            rear = newNode;
        }
        cout << val << " enqueued into the queue." << endl;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is Empty (Underflow)!" << endl;
            return -1;
        }
        int removed = front->data;
        Node* temp = front;
        front = front->next;

        // If front becomes NULL, queue is now empty
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp; // Free the memory of removed node
        return removed;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        cout << "Queue elements (Front to Rear): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    Queue q;
    int option, value;

    do {
        cout << "\nChoose an operation (Enter 0 to Exit):" << endl;
        cout << "1. Enqueue()\n2. Dequeue()\n3. isEmpty()\n4. Display()\n";
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
