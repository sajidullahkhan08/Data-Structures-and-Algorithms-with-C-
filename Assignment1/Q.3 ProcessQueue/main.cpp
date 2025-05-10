#include <iostream>
#include <fstream>
using namespace std;

// ----------------------------
// Process Node (Doubly Linked List)
// ----------------------------
class Process {
public:
    int PID;
    int priority;
    int arrivalTime;
    Process* next;
    Process* prev;

    Process(int id, int p, int time) {
        PID = id;
        priority = p;
        arrivalTime = time;
        next = prev = nullptr;
    }
};

// ----------------------------
// Process Queue (Doubly Linked List Implementation)
// ----------------------------
class ProcessQueue {
private:
    Process* head;
public:
    ProcessQueue() { head = nullptr; }

    // Enqueue (Insert process based on priority)
    void enqueue(int id, int priority, int arrivalTime) {
        Process* newProcess = new Process(id, priority, arrivalTime);

        // If queue is empty
        if (!head) {
            head = newProcess;
            return;
        }

        Process* current = head;
        Process* prev = nullptr;

        // Find the correct position based on priority & arrival time
        while (current && (current->priority > priority || 
              (current->priority == priority && current->arrivalTime <= arrivalTime))) {
            prev = current;
            current = current->next;
        }

        // Insert at the beginning
        if (!prev) {
            newProcess->next = head;
            head->prev = newProcess;
            head = newProcess;
        } 
        // Insert at the correct position
        else {
            newProcess->next = current;
            newProcess->prev = prev;
            prev->next = newProcess;
            if (current) current->prev = newProcess;
        }
    }

    // Dequeue (Remove highest-priority process)
    void dequeue() {
        if (!head) {
            cout << "Queue is empty!\n";
            return;
        }

        Process* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;

        cout << "Dequeued Process - PID: " << temp->PID << ", Priority: " << temp->priority << endl;
        delete temp;
    }

    // Display Queue
    void displayQueue() {
        if (!head) {
            cout << "Queue is empty!\n";
            return;
        }

        cout << "\nCurrent Process Queue:\n";
        cout << "PID\tPriority\tArrival Time\n";
        for (Process* temp = head; temp; temp = temp->next) {
            cout << temp->PID << "\t" << temp->priority << "\t\t" << temp->arrivalTime << endl;
        }
    }

    // Read from file (Load processes into queue)
    void readFromFile(string filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error: Cannot open file " << filename << endl;
            return;
        }

        int id, priority, arrivalTime;
        while (file >> id >> priority >> arrivalTime) {
            enqueue(id, priority, arrivalTime);
        }

        file.close();
    }

    // Write queue to file
    void writeToFile(string filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error: Cannot write to file " << filename << endl;
            return;
        }

        for (Process* temp = head; temp; temp = temp->next) {
            file << temp->PID << " " << temp->priority << " " << temp->arrivalTime << endl;
        }

        file.close();
    }
};

// ----------------------------
// Main Function (User Interface)
// ----------------------------
int main() {
    ProcessQueue queue;
    queue.readFromFile("process.txt");

    int choice;
    do {
        cout << "\n--- Process Queue Management ---\n";
        cout << "1. Enqueue Process\n";
        cout << "2. Dequeue Process\n";
        cout << "3. Display Queue\n";
        cout << "4. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, priority, arrival;
                cout << "Enter Process ID: ";
                cin >> id;
                cout << "Enter Priority (higher value = higher priority): ";
                cin >> priority;
                cout << "Enter Arrival Time: ";
                cin >> arrival;
                queue.enqueue(id, priority, arrival);
                break;
            }
            case 2:
                queue.dequeue();
                break;
            case 3:
                queue.displayQueue();
                break;
            case 4:
                queue.writeToFile("process.txt");
                cout << "Queue saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
