#include <iostream>

using namespace std;

class PriorityQueue {
    public:
        static const int MAX = 10;
        int PQArray[MAX];
        int priority[MAX];
        int size;

        PriorityQueue() {
            size = 0;
        }

        void enqueue(int value, int prio) {
            if (size < MAX) {
                PQArray[size] = value;
                priority[size] = prio;
                size++;
            } 
            else {
                cout << "Queue is already full!" << endl;
            }
        }

        int dequeue() {
            if (size == 0) {
                cout << "Queue already is empty!" << endl;
                return -1;
            }
            int maxIndex = 0;
            for (int i = 1; i < size; i++) {
                if (priority[i] > priority[maxIndex]) {
                    maxIndex = i;
                }
            }
            int maxValue = PQArray[maxIndex];

            for (int i = maxIndex; i < size - 1; i++) {
                PQArray[i] = PQArray[i + 1];
                priority[i] = priority[i + 1];
            }
            size--;
            return maxValue;
        }
};

int main() {
    PriorityQueue PQ;

    PQ.enqueue(9, 7);
    PQ.enqueue(5, 3);
    PQ.enqueue(2, 5);
    PQ.enqueue(8, 6);
    PQ.enqueue(1, 2);
    PQ.enqueue(4, 1);

    while (PQ.size > 0) {
        cout << "Dequeued: " << PQ.dequeue() << endl;
    }

    return 0;
}