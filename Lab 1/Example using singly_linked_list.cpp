#include <iostream>
#include <string>

using namespace std;

struct Employee {
    string name, fname, education;
    int emp_id;

    Employee * next;

    Employee(string n, string f, string e, int id) {
        name = n;
        fname = f;
        education = e;
        emp_id = id;
        next = NULL;
    }
};

class EmployeesList {
    Employee * head;

    public:
        EmployeesList () {
            head = NULL;
        }

        void insert_at_beginning(string name, string fname, string education, int emp_id) {
            Employee * newEmployee = new Employee(name, fname, education, emp_id);
            newEmployee->next = head;
            head = newEmployee;
        }

        void insert_at_end(string name, string fname, string education, int emp_id) {
            Employee * newEmployee = new Employee(name, fname, education, emp_id);

            if(head == NULL) {
                head = newEmployee;
            }
            Employee * temp = head;

            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newEmployee;
        }

        void insert_at_Middle(string name, string fname, string education, int emp_id, int after_id) {
            Employee * temp = head;
            while(temp != NULL && temp->emp_id != after_id) {
                temp = temp->next;
            }
            if(temp == NULL) {
                cout << "Employees List is empty.";
                return;
            }

            Employee * newEmployee = new Employee(name, fname, education, emp_id);
                newEmployee->next = temp->next;
                temp->next = newEmployee;
        }

        void delete_Employee(int emp_id) {
            if(head == NULL) {
                cout << "Already empty.";
                return;
            }
            if(head->emp_id == emp_id) {
                Employee * temp = head;
                head = head-> next;
                delete temp;
                return;
            }
            Employee * temp = head;
            while (temp->next != NULL && temp->next->emp_id != emp_id)
                temp = temp->next;
            if (temp->next == NULL) {
                cout << "Employee ID not found.\n";
                return;
            }
            Employee * toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }

        void search(int emp_id) {
            Employee * search(int emp_id); 
                Employee * temp = head;
                while (temp != NULL) {
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
                cout << "Employee ID not found.";
        }

        void display() {
            Employee * temp = head;
            while(temp != NULL) {
                cout << "Name: " << temp->name <<endl;
                cout << "Father Name: " << temp->fname <<endl;
                cout << "Education: " << temp->education <<endl;
                cout << "Employee ID: " << temp->emp_id <<endl;
                temp = temp->next;
                cout <<endl;
            }
        }
};

int main() {
    EmployeesList list;

    //Insert at the beginning
    list.insert_at_beginning("Sajid", "Aziz", "BSCS", 4995);
    list.insert_at_beginning("Nouman", "Rana", "BSIT", 4996);
    cout << "At the Beginning:" <<endl <<endl;
    list.display();

    //Insert at the end
    list.insert_at_end("Areeb", "Khan", "BSSE", 4994);
    list.insert_at_end("Arif", "Hussain", "MSCS", 4990);
    cout << "At the End:" <<endl <<endl;
    list.display();

    //Insert at the middle
    list.insert_at_Middle("Ali", "Raza", "BSCS", 4993, 4996);
    cout << "At the Middle:" <<endl <<endl;
    list.display();

    //Search an employee
    cout << "Searched:" <<endl;
    list.search(4995);

    //Delete an employee
    list.delete_Employee(4996);
    cout << "Deleted: 4996" <<endl <<endl;
    list.display();
}