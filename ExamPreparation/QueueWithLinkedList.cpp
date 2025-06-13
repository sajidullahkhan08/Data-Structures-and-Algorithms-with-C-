#include <iostream>
using namespace std;

struct Node {
    Node * next;
    int data;

    Node() {
        next = NULL;
        data = 0;
    }
};

class Queue {
    public:
        Node * front;
        Node * rear;

        Queue() {
            front = rear = NULL;
        }

        void enqueue(int value) {
            Node * newNode = new Node();
            if(front == NULL && rear == NULL) {
                front = rear = newNode;
                newNode->data = value;
                newNode->next = NULL;
            }
            else {
                rear->next = newNode;
                newNode->data = value;
                rear = newNode;
            }
            cout << value << " Enuqueued Successfully!" <<endl;
        }

        int dequeue() {
            if(front == NULL && rear == NULL) {
                cout << "Queue is already empty!" <<endl;
                return -1;
            }
            else if(front == rear) {
                int removed = front->data;
                Node * temp = front;
                front = rear = NULL;
                delete temp;
                return removed;
            }
            else {
                int removed = front->data;
                Node * temp = front;
                front = front->next;
                delete temp;
                return removed;
            }
        }

        void display() {
            if(front == NULL && rear == NULL) {
                cout << "The Queue is empty!" <<endl;
            }
            else {
                Node * temp = front;
                while(temp != NULL) {
                    cout << temp->data << " ";
                    temp = temp->next;
                }
                cout << endl;
            }
        }
};

int main() {
    Queue Q;

    Q.enqueue(1);
    Q.enqueue(2);
    Q.enqueue(3);
    Q.enqueue(4);

    cout << "The Dequeued value is: " << Q.dequeue() <<endl;

    Q.display();
    
    return 0;
}