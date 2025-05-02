#include <iostream>
using namespace std;

// stack implementation using Linked List
class Node {
    public:
        int data;
        Node* next;

        Node() {
            data = 0;
            next = NULL;
        }
};

class LinkedListStack {
    private:
        Node* top;
    public:
        LinkedListStack() {
            top = NULL;
        }

    bool isEmpty() {
            return (top == NULL);
    }

    void push(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    void peek() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Top element is " << top->data << endl;
    }
};

int main() {
    LinkedListStack s;
        s.push(10);
        s.push(20);
        s.push(30);

        s.peek();
        s.pop();
        s.peek();
        s.pop();
        s.peek();
        s.pop();
        s.peek();

    return 0;
}