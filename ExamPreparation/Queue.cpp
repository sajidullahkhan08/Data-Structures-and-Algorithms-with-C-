#include <iostream>
using namespace std;

template <class Type>

class Queue {
    private:
        Type QArray[10];
        int front, rear;
    public:
        Queue () {
            front = rear = -1;
            for(int i = 0; i < 10; i++) {
                QArray[i] = 0;
            }
        }

        void enqueue(Type value) {
            if(rear == 9) {
                cout << "Queue is full!" <<endl;
            }
            else if(front == -1 && rear == -1) {
                front = rear = 0;
                QArray[rear] = value;
            }
            else {
                QArray[++rear] = value;
            }
        }

        Type dequeue() {
            if((front && rear) == -1) {
                cout << "Queue is empty!" <<endl;
                return 0;
            }
            else {
                Type temp = QArray[front];
                if(front == rear) {
                    front = rear = -1;
                }
                else {
                front++;
                }
                return temp;
            }
        }
};

int main() {
    Queue<int> Q;
    Q.enqueue(2);
    Q.enqueue(3);
    Q.enqueue(4);

    cout << "Dequeued: " << Q.dequeue() << endl;
    cout << "Dequeued: " << Q.dequeue() << endl;

    return 0;
}
