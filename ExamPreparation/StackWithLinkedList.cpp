#include <iostream>
using namespace std;

struct Node {
    int data;
    Node * next;

    Node () {
        next = NULL;
        data = 0;
    }
};

class Stack {
    public:
        Node * top;
        
        Stack () {
            top = NULL;
        }

        void push(int value) {
            Node * newNode = new Node();
            if(top == NULL) {
                newNode->data = value;
                newNode->next = NULL;
                top = newNode;
            }
            else {
                newNode->data = value;
                newNode->next = top;
                top = newNode;
            }
        }

        void pop() {
            if(top == NULL) {
                cout << "Stack is empty!" <<endl;
                return;
            }
            else {
                Node * temp = top;
                top = temp->next;
                cout << "The poped value is: " << temp->data;
                delete temp;
            }
        }

        void peek() {
            if(top == NULL) {
                cout << "Stack is empty!" <<endl;
                return;
            }
            else {
                cout << "Top Element is: " << top->data <<endl;
            }
        }
};

int main() {
    Stack S;

    S.push(1);
    S.push(2);
    S.push(3);
    S.push(4);

    S.pop();
    cout << endl;

    S.peek();
    S.push(6);
    S.peek();

    return 0;
}