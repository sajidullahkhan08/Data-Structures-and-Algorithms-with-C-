#include <iostream>
#include <string>

using namespace std;

struct Employee {
    string name, fname, education;
    int emp_id;
    Employee *next, *prev;

    Employee(string n, string f, string e, int id) {
        name = n;
        fname = f;
        education = e;
        emp_id = id;
        next = prev = nullptr;
    }
};

class EmployeesList {
    Employee *head, *tail;

public:
    EmployeesList() {
        head = nullptr;
        tail = nullptr;
    }

    void insert_at_beginning(string name, string fname, string education, int emp_id) {
        Employee *newEmployee = new Employee(name, fname, education, emp_id);
        if (head == nullptr) {
            head = tail = newEmployee;
        } else {
            newEmployee->next = head;
            head->prev = newEmployee;
            head = newEmployee;
        }
    }

    void insert_at_end(string name, string fname, string education, int emp_id) {
        Employee *newEmployee = new Employee(name, fname, education, emp_id);
        if (head == nullptr) {
            head = tail = newEmployee;
        } else {
            tail->next = newEmployee;
            newEmployee->prev = tail;
            tail = newEmployee;
        }
    }

    void insert_at_Middle(string name, string fname, string education, int emp_id, int after_id) {
        Employee *temp = head;
        while (temp != nullptr && temp->emp_id != after_id) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Employee ID not found.\n";
            return;
        }

        Employee *newEmployee = new Employee(name, fname, education, emp_id);
        newEmployee->next = temp->next;
        newEmployee->prev = temp;

        if (temp->next != nullptr) {
            temp->next->prev = newEmployee;
        }
        temp->next = newEmployee;

        if (temp == tail) {
            tail = newEmployee;
        }
    }

    void delete_Employee(int emp_id) {
        if (head == nullptr) {
            cout << "List is already empty.\n";
            return;
        }

        Employee *temp = head;

        while (temp != nullptr && temp->emp_id != emp_id) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Employee ID not found.\n";
            return;
        }

        if (temp == head) {
            head = temp->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        } else if (temp == tail) {
            tail = temp->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
    }

    void search(int emp_id) {
        Employee *temp = head;
        while (temp != nullptr) {
            if (temp->emp_id == emp_id) {
                cout << "Employee found: " <<endl;
                        cout << "Name: " << temp->name <<endl;
                        cout << "Father Name: " << temp->fname <<endl;
                        cout << "Education: " << temp->education <<endl;
                        cout << "Employee ID: " << temp->emp_id <<endl;
                        return;
            }
            temp = temp->next;
        }
        cout << "Employee ID not found.\n";
    }

    void display_forward() {
        Employee *temp = head;
        while (temp != nullptr) {
            cout << "Name: " << temp->name << endl;
            cout << "Father Name: " << temp->fname << endl;
            cout << "Education: " << temp->education << endl;
            cout << "Employee ID: " << temp->emp_id << endl;
            temp = temp->next;
            cout << endl;
        }
    }

    void display_backward() {
        Employee *temp = tail;
        while (temp != nullptr) {
            cout << "Name: " << temp->name << endl;
            cout << "Father Name: " << temp->fname << endl;
            cout << "Education: " << temp->education << endl;
            cout << "Employee ID: " << temp->emp_id << endl;
            temp = temp->prev;
            cout << endl;
        }
    }
};

int main() {
    EmployeesList list;

    // Insert at the beginning
    list.insert_at_beginning("Sajid", "Aziz", "BSCS", 4995);
    list.insert_at_beginning("Nouman", "Rana", "BSIT", 4996);
    cout << "At the Beginning (Forward):\n";
    list.display_forward();

    // Insert at the end
    list.insert_at_end("Areeb", "Khan", "BSSE", 4994);
    list.insert_at_end("Arif", "Hussain", "MSCS", 4990);
    cout << "At the End (Forward):\n";
    list.display_forward();

    // Insert at the middle
    list.insert_at_Middle("Ali", "Raza", "BSCS", 4993, 4996);
    cout << "At the Middle (Forward):\n";
    list.display_forward();

    // Display in reverse order
    cout << "Display Backward:\n";
    list.display_backward();

    // Search an employee
    cout << "Search Result:\n";
    list.search(4995);

    // Delete an employee
    list.delete_Employee(4996);
    cout << "Deleted: 4996\n";
    cout << "Updated List (Forward):\n";
    list.display_forward();

    return 0;
}