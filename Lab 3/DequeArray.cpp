#include <iostream>
using namespace std;

class Deque {
private:
    int arr[5];
    int front;
    int rear;
    int size;

public:
    Deque() {
        size = 5;
        front = -1;
        rear = -1;
        for (int i = 0; i < size; i++) {
            arr[i] = 0;
        }
    }

    bool isFull() {
        return (front == 0 && rear == size - 1) || (front == rear + 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void insertFront(int val) {
        if (isFull()) {
            cout << "Deque is Full (Overflow)!" << endl;
            return;
        }

        if (isEmpty()) {
            front = rear = 0;
        } else if (front == 0) {
            front = size - 1;
        } else {
            front--;
        }

        arr[front] = val;
        cout << val << " inserted at front." << endl;
    }

    void insertRear(int val) {
        if (isFull()) {
            cout << "Deque is Full (Overflow)!" << endl;
            return;
        }

        if (isEmpty()) {
            front = rear = 0;
        } else if (rear == size - 1) {
            rear = 0;
        } else {
            rear++;
        }

        arr[rear] = val;
        cout << val << " inserted at rear." << endl;
    }

    void deleteFront() {
        if (isEmpty()) {
            cout << "Deque is Empty (Underflow)!" << endl;
            return;
        }

        cout << "Deleted from front: " << arr[front] << endl;
        arr[front] = 0;

        if (front == rear) {
            front = rear = -1;
        } else if (front == size - 1) {
            front = 0;
        } else {
            front++;
        }
    }

    void deleteRear() {
        if (isEmpty()) {
            cout << "Deque is Empty (Underflow)!" << endl;
            return;
        }

        cout << "Deleted from rear: " << arr[rear] << endl;
        arr[rear] = 0;

        if (front == rear) {
            front = rear = -1;
        } else if (rear == 0) {
            rear = size - 1;
        } else {
            rear--;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Deque is Empty!" << endl;
            return;
        }

        cout << "Deque elements: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear)
                break;
            i = (i + 1) % size;
        }
        cout << endl;
    }

    void showIndexes() {
        cout << "Front index: " << front << ", Rear index: " << rear << endl;
    }

    void getFront() {
        if (isEmpty()) {
            cout << "Deque is Empty!" << endl;
        } else {
            cout << "Front element: " << arr[front] << endl;
        }
    }

    void getRear() {
        if (isEmpty()) {
            cout << "Deque is Empty!" << endl;
        } else {
            cout << "Rear element: " << arr[rear] << endl;
        }
    }
};

int main() {
    Deque dq;
    int option, value;

    do {
        cout << "\nChoose an operation (Enter 0 to Exit):" << endl;
        cout << "1. Insert Front\n2. Insert Rear\n3. Delete Front\n4. Delete Rear\n";
        cout << "5. Display\n6. Show Indexes\n7. Get Front\n8. Get Rear\n";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Enter value to insert at front: ";
                cin >> value;
                dq.insertFront(value);
                break;
            case 2:
                cout << "Enter value to insert at rear: ";
                cin >> value;
                dq.insertRear(value);
                break;
            case 3:
                dq.deleteFront();
                break;
            case 4:
                dq.deleteRear();
                break;
            case 5:
                dq.display();
                break;
            case 6:
                dq.showIndexes();
                break;
            case 7:
                dq.getFront();
                break;
            case 8:
                dq.getRear();
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
