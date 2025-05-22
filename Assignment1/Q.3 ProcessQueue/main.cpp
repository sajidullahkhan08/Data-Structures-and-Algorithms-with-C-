#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

struct time {
    int hour, minute, second;
    
    void parseTime(string timeStr){
    sscanf(timeStr.c_str(), "%d.%d.%d", &hour, &minute, &second);
    }

    void getCurrentTime(){
        time_t now =::time(0);
        tm* ltm = localtime(&now);
        hour=ltm->tm_hour;
        minute=ltm->tm_min;
        second=ltm->tm_sec;
    }
    string toString() {
        string h =(hour < 10 ? "0" : "")+to_string(hour);
        string m =(minute < 10 ? "0" : "")+to_string(minute);
        string s =(second < 10 ? "0" : "")+to_string(second);
        return h + "." + m + "." + s;
    }
    bool isLessThan(struct time t) {
        if(hour != t.hour)
            return hour < t.hour;
        if(minute != t.minute)
            return minute < t.minute;
        return second < t.second;
    }
};

struct Process {
    string processName;
    int priorityLevel;
    struct time entryTime;
    Process* next;
    Process* prev;
    
    Process(string name, int priority, struct time entry) {
        processName=name;
        priorityLevel=priority;
        entryTime=entry;
        next=NULL;
        prev=NULL;
    }
};

class PriorityQueue {
private:
    Process* head;
    Process* tail;
    
public:
    PriorityQueue(){
        head = NULL;
        tail = NULL;
    }
    bool isEmpty() {
        return head == NULL;
    }
    void enqueue(string name, int priority, struct time entry) {
        Process* newProcess = new Process(name, priority, entry);
        if(isEmpty()){
            head = tail = newProcess;
            return;}
        if(priority > head->priorityLevel){
            newProcess->next = head;
            head->prev = newProcess;
            head = newProcess;
            return;
        }
        Process* current = head;
        while(current != nullptr){
            if(current->priorityLevel < priority){
                break;}
            if(current->priorityLevel == priority && 
                !current->entryTime.isLessThan(entry)){
                break;}
            current = current->next;
        }
        if (current == NULL) {
            tail->next = newProcess;
            newProcess->prev = tail;
            tail = newProcess;
        }
        else {
            if (current->prev != NULL){
                current->prev->next = newProcess;
                newProcess->prev = current->prev;
            } else {
                head = newProcess;
            }
            newProcess->next=current;
            current->prev=newProcess;
        }
    }
    
    void dequeue() {
        if(isEmpty()){
            cout << "Queue is empty!" << endl;
            return;}
        Process* temp = head;
        if (head == tail) {
            head = tail = NULL;
        } else {
            head = head->next;
            head->prev = NULL;
        }
        cout<<"Removed Process: " <<temp->processName 
             << ", Priority: "<<temp->priorityLevel 
             << ", Entry Time: "<<temp->entryTime.toString() <<endl;
        delete temp;
    }

    void display(){
        if(isEmpty()){
            cout <<"Queue is empty!"<<endl;
            return;}
        cout<<"\nProcess Queue Contents:"<<endl;
        cout<<"Process Name\tPriority\tEntry Time" <<endl;
        cout<<"----------------------------------------"<<endl;
        
        Process* current = head;
        while (current != NULL) {
            cout << current->processName << "\t\t" 
                 << current->priorityLevel << "\t\t" 
                 << current->entryTime.toString() << endl;
            current = current->next;
        }
    }
    
    void readFromFile(string filename) {
        ifstream file(filename);
        
        if(!file.is_open()){
            cout<< "Error: Unable to open file "<<filename<<endl;
            return;}
        
        string name;
        int priority;
        string timeStr;
        while(file >> name >> priority >> timeStr){
            struct time entryTime;
            entryTime.parseTime(timeStr);
            enqueue(name, priority, entryTime);
        }
        
        file.close();
        cout << "Processes loaded and added from file successfully." << endl;
    }

    ~PriorityQueue(){
        Process* current=head;
        while(current!=NULL){
            Process* temp=current;
            current=current->next;
            delete temp;}
    }
};

int main(){
    PriorityQueue pq;
    pq.readFromFile("process.txt");
    
    int choice;
    do {
        cout << "\nPriority Queue Operations:"<<endl;
        cout << "1. Display all processes"<<endl;
        cout << "2. Add a new process"<<endl;
        cout << "3. Remove highest priority process"<<endl;
        cout << "0. Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 
        
        switch(choice){
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
                struct time currentTime;
                currentTime.getCurrentTime();
                pq.enqueue(name, priority, currentTime);
                cout << "Process added successfully with entry time: " 
                     << currentTime.toString() <<endl;
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