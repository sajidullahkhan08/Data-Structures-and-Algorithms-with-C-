#include <iostream>
using namespace std;

class ArrayStack {
private:
    int top;
    int arr[10];

public:
    ArrayStack() {
        top = -1;
    }

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == 9); // Assuming size of stack is 10 (size-1=9)
    }

    void push(int data) {
        if (!isFull()) {
            arr[++top] = data;
        } else {
            cout << "Stack Overflow" << endl;
        }
    }

    void pop() {
        if (!isEmpty()) {
            top--;
        } else {
            cout << "Stack Underflow" << endl;
        }
    }

    void peek() {
        if (!isEmpty()) {
            cout << "Top element is: " << arr[top] << endl;
        } else {
            cout << "Stack is empty" << endl;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack elements (top to bottom): ";
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    ArrayStack s;

    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);
    s.push(60); // Should cause overflow

    s.display();

    s.peek();

    s.pop();
    s.pop();

    s.display();
    s.peek();

    return 0;
}
