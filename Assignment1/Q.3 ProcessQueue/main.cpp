#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// Structure for storing time
struct time {
    int hour;
    int minute;
    int second;
    
    // Parse time from string (format: HH.MM.SS)
    void parseTime(string timeStr) {
        int pos1 = timeStr.find('.');
        int pos2 = timeStr.rfind('.');
        
        hour = stoi(timeStr.substr(0, pos1));
        minute = stoi(timeStr.substr(pos1 + 1, pos2 - pos1 - 1));
        second = stoi(timeStr.substr(pos2 + 1));
    }
    
    // Get current system time
    void getCurrentTime() {
        time_t now = ::time(0);
        tm* ltm = localtime(&now);
        hour = ltm->tm_hour;
        minute = ltm->tm_min;
        second = ltm->tm_sec;
    }
    
    // Convert time to string
    string toString() {
        char buffer[9];
        sprintf(buffer, "%02d.%02d.%02d", hour, minute, second);
        return string(buffer);
    }
    
    // Compare with another time
    bool isLessThan(struct time t) {
        if (hour != t.hour)
            return hour < t.hour;
        if (minute != t.minute)
            return minute < t.minute;
        return second < t.second;
    }
};

// Process node for the doubly linked list
struct Process {
    string processName;
    int priorityLevel;
    struct time entryTime;
    Process* next;
    Process* prev;
    
    // Constructor
    Process(string name, int priority, struct time entry) {
        processName = name;
        priorityLevel = priority;
        entryTime = entry;
        next = nullptr;
        prev = nullptr;
    }
};

// Priority Queue implementation using doubly linked list
class PriorityQueue {
private:
    Process* head;
    Process* tail;
    
public:
    // Constructor
    PriorityQueue() {
        head = nullptr;
        tail = nullptr;
    }
    
    // Destructor
    ~PriorityQueue() {
        Process* current = head;
        while (current != nullptr) {
            Process* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    // Check if queue is empty
    bool isEmpty() {
        return head == nullptr;
    }
    
    // Enqueue a process based on priority and entry time
    void enqueue(string name, int priority, struct time entry) {
        Process* newProcess = new Process(name, priority, entry);
        
        // If queue is empty
        if (isEmpty()) {
            head = tail = newProcess;
            return;
        }
        
        // If new process has higher priority than head
        if (priority > head->priorityLevel) {
            newProcess->next = head;
            head->prev = newProcess;
            head = newProcess;
            return;
        }
        
        // Find position to insert based on priority and entry time
        Process* current = head;
        
        while (current != nullptr) {
            // Found position based on priority
            if (current->priorityLevel < priority) {
                break;
            }
            
            // Same priority, check entry time
            if (current->priorityLevel == priority && 
                !current->entryTime.isLessThan(entry)) {
                break;
            }
            
            current = current->next;
        }
        
        // Insert at the end
        if (current == nullptr) {
            tail->next = newProcess;
            newProcess->prev = tail;
            tail = newProcess;
        }
        // Insert in the middle or at the beginning
        else {
            if (current->prev != nullptr) {
                // In the middle
                current->prev->next = newProcess;
                newProcess->prev = current->prev;
            } else {
                // At the beginning
                head = newProcess;
            }
            
            newProcess->next = current;
            current->prev = newProcess;
        }
    }
    
    // Dequeue highest priority process
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        
        Process* temp = head;
        
        // If only one process
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        
        cout << "Removed Process: " << temp->processName 
             << ", Priority: " << temp->priorityLevel 
             << ", Entry Time: " << temp->entryTime.toString() << endl;
        
        delete temp;
    }
    
    // Display all processes in the queue
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        
        cout << "\nProcess Queue Contents:" << endl;
        cout << "Process Name\tPriority\tEntry Time" << endl;
        cout << "----------------------------------------" << endl;
        
        Process* current = head;
        while (current != nullptr) {
            cout << current->processName << "\t\t" 
                 << current->priorityLevel << "\t\t" 
                 << current->entryTime.toString() << endl;
            current = current->next;
        }
    }
    
    // Read processes from file
    void readFromFile(string filename) {
        ifstream file(filename);
        
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }
        
        string name;
        int priority;
        string timeStr;
        
        while (file >> name >> priority >> timeStr) {
            struct time entryTime;
            entryTime.parseTime(timeStr);
            
            enqueue(name, priority, entryTime);
        }
        
        file.close();
        cout << "Processes loaded from file successfully." << endl;
    }
};

int main() {
    PriorityQueue pq;
    
    // Read processes from file
    pq.readFromFile("process.txt");
    
    int choice;
    
    do {
        cout << "\nPriority Queue Operations:" << endl;
        cout << "1. Display all processes" << endl;
        cout << "2. Add a new process" << endl;
        cout << "3. Remove highest priority process" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 
        
        switch (choice) {
            case 1:
                pq.display();
                break;
                
            case 2: {
                string name;
                int priority;
                
                cout << "Enter Process Name: ";
                getline(cin, name);
                
                cout << "Enter Priority Level: ";
                cin >> priority;
                
                // Get current system time for entry time
                struct time currentTime;
                currentTime.getCurrentTime();
                
                pq.enqueue(name, priority, currentTime);
                cout << "Process added successfully with entry time: " 
                     << currentTime.toString() << endl;
                break;
            }
                
            case 3:
                pq.dequeue();
                break;
                
            case 0:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
    } while (choice != 0);
    
    return 0;
}