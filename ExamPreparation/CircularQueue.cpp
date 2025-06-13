#include <iostream>
using namespace std;

class Queue {
    public:
        int front, rear;
        int QArray[10];
        
        Queue() {
            front = rear = -1;
            for(int i = 0; i < 10; i++) {
                QArray[i] = 0;
            }
        }

        void enqueue(int item) {
            if(front == -1) {
                front = rear = 0;
            }
            else if()
        }
};