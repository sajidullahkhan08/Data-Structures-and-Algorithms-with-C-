// Part A: Student Record Management using Hash Table (No STL Used)
#include <iostream>
#include <cstring> // for strcpy
using namespace std;

// Structure for each Student
struct Student {
    int rollNumber;
    char name[50];
    char department[30];
    float cgpa;
    Student* next; // for chaining
};

// Hash Table class
class StudentHashTable {
private:
    int size;
    Student** table; // array of pointers to Student

    int hashFunction(int roll) {
        return roll % size;
    }

public:
    StudentHashTable(int s) {
        size = s;
        table = new Student*[size];
        for (int i = 0; i < size; i++) table[i] = nullptr;
    }

    void insert(int roll, const char* name, const char* dept, float cgpa) {
        int index = hashFunction(roll);
        Student* newStudent = new Student{roll, "", "", cgpa, nullptr};
        strcpy(newStudent->name, name);
        strcpy(newStudent->department, dept);
        newStudent->next = table[index];
        table[index] = newStudent;
        cout << "Student inserted successfully.\n";
    }

    void search(int roll) {
        int index = hashFunction(roll);
        Student* current = table[index];
        while (current) {
            if (current->rollNumber == roll) {
                cout << "\nStudent Found:\n";
                cout << "Roll Number: " << current->rollNumber << endl;
                cout << "Name: " << current->name << endl;
                cout << "Department: " << current->department << endl;
                cout << "CGPA: " << current->cgpa << endl;
                return;
            }
            current = current->next;
        }
        cout << "Student not found.\n";
    }

    void deleteRecord(int roll) {
        int index = hashFunction(roll);
        Student* current = table[index];
        Student* prev = nullptr;
        while (current) {
            if (current->rollNumber == roll) {
                if (prev)
                    prev->next = current->next;
                else
                    table[index] = current->next;
                delete current;
                cout << "Student deleted successfully.\n";
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Student not found.\n";
    }

    void display() {
        cout << "\n--- Student Records ---\n";
        for (int i = 0; i < size; i++) {
            cout << "Bucket " << i << ": ";
            Student* current = table[i];
            while (current) {
                cout << "[" << current->rollNumber << ", " << current->name << ", " << current->department << ", " << current->cgpa << "] -> ";
                current = current->next;
            }
            cout << "NULL\n";
        }
    }

    ~StudentHashTable() {
        for (int i = 0; i < size; i++) {
            Student* current = table[i];
            while (current) {
                Student* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }
};

int main() {
    int size;
    cout << "Enter hash table size: ";
    cin >> size;
    StudentHashTable ht(size);

    int choice;
    do {
        cout << "\n=== Student Hash Table Menu ===\n";
        cout << "1. Insert Student\n2. Search Student\n3. Delete Student\n4. Display All\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int roll;
            char name[50], dept[30];
            float cgpa;
            cout << "Enter Roll Number: "; cin >> roll;
            cin.ignore();
            cout << "Enter Name: "; cin.getline(name, 50);
            cout << "Enter Department: "; cin.getline(dept, 30);
            cout << "Enter CGPA: "; cin >> cgpa;
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
