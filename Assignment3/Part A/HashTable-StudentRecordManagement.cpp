#include <iostream>
#include <string>
using namespace std;

struct Student{
    int rollNumber;
    string name;
    string department;
    float cgpa;
    Student* next;
};

class StudentHashTable {
private:
    int size;
    Student** table;

    int hashFunction(int roll){
        return roll % size;}

public:
    StudentHashTable(int s){
        size = s;
        table = new Student*[size];
        for (int i = 0; i < size; i++) table[i] = NULL;
    }

    void insert(int roll, string& name, string& dept, float cgpa) {
        int index = hashFunction(roll);
        Student* newStudent = new Student;
        newStudent->rollNumber = roll;
        newStudent->cgpa = cgpa;
        newStudent->name = name;
        newStudent->department = dept;
        newStudent->next = table[index];
        table[index] = newStudent;
        cout<<"Student inserted successfully.\n";
    }

    void search(int roll){
        int index = hashFunction(roll);
        Student* current = table[index];
        while(current){
            if (current->rollNumber == roll) {
                cout<<"\nStudent Found:\n";
                cout<<"Roll Number: "<<current->rollNumber<<endl;
                cout<<"Name: "<<current->name<<endl;
                cout<<"Department: "<< current->department<<endl;
                cout<<"CGPA: "<<current->cgpa<<endl;
                return;
            }
            current = current->next;
        }
        cout<<"Student not found.\n";
    }

    void deleteRecord(int roll) {
        int index = hashFunction(roll);
        Student* current = table[index];
        Student* prev = NULL;
        while(current){
            if(current->rollNumber == roll){
                if(prev)
                    prev->next = current->next;
                else
                    table[index] = current->next;
                delete current;
                cout<<"Student deleted successfully.\n";
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Student not found.\n";
    }

    void display(){
        cout<<"\n--- Student Records ---\n";
        for(int i = 0; i < size; i++){
            cout<<"Bucket "<<i<<": ";
            Student* current = table[i];
            while(current){
                cout<<"["<< current->rollNumber<< ", "<< current->name<< ", " << current->department << ", " << current->cgpa << "] -> ";
                current = current->next;
            }
            cout<<"NULL\n";
        }
    }

    ~StudentHashTable(){
        for (int i = 0; i < size; i++){
            Student* current = table[i];
            while(current){
                Student* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }
};

int main(){
    int size;
    cout<<"Enter hash table size: ";
    cin>>size;
    StudentHashTable ht(size);

    int choice;
    do {
        cout << "\n=== Student Hash Table Menu ===\n";
        cout << "1. Insert Student\n2. Search Student\n3. Delete Student\n4. Display All\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            int roll;
            float cgpa;
            cout<<"Enter Roll Number: "; cin >> roll;
            cin.ignore();
            string name, dept;
            cout<<"Enter Name: "; getline(cin, name);
            cout<<"Enter Department: "; getline(cin, dept);
            cout<<"Enter CGPA: "; cin >> cgpa;
            ht.insert(roll, name, dept, cgpa);
        } else if (choice == 2) {
            int roll;
            cout << "Enter Roll Number to search: "; cin >> roll;
            ht.search(roll);
        } else if (choice == 3) {
            int roll;
            cout << "Enter Roll Number to delete: "; cin >> roll;
            ht.deleteRecord(roll);
        } else if (choice == 4) {
            ht.display();
        } else if (choice != 5) {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
    cout << "Program exited.\n";
    return 0;
}
