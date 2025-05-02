#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

// Circular Linked List class
class CircularLinkedList {
    Node* head;

public:
    CircularLinkedList() {
        head = NULL;
    }

    // Insert at beginning
    void insert_at_beginning(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            newNode->next = newNode;
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != head)
            temp = temp->next;

        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }

    // Insert at end
    void insert_at_end(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            newNode->next = newNode;
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != head)
            temp = temp->next;

        temp->next = newNode;
        newNode->next = head;
    }

    // Insert at specific position (1-based)
    void insert_at_position(int val, int pos) {
        if (pos < 1) {
            cout << "Invalid position.\n";
            return;
        }

        if (pos == 1) {
            insert_at_beginning(val);
            return;
        }

        Node* temp = head;
        int count = 1;
        while (count < pos - 1 && temp->next != head) {
            temp = temp->next;
            count++;
        }

        if (count != pos - 1) {
            cout << "Position out of bounds.\n";
            return;
        }

        Node* newNode = new Node(val);
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Delete from beginning
    void delete_from_beginning() {
        if (head == NULL) {
            cout << "List is already empty.\n";
            return;
        }

        if (head->next == head) {
            delete head;
            head = NULL;
            return;
        }

        Node* temp = head;
        while (temp->next != head)
            temp = temp->next;

        Node* toDelete = head;
        head = head->next;
        temp->next = head;
        delete toDelete;
    }

    // Delete from end
    void delete_from_end() {
        if (head == NULL) {
            cout << "List is already empty.\n";
            return;
        }

        if (head->next == head) {
            delete head;
            head = NULL;
            return;
        }

        Node* temp = head;
        while (temp->next->next != head)
            temp = temp->next;

        Node* toDelete = temp->next;
        temp->next = head;
        delete toDelete;
    }

    // Delete from specific position
    void delete_from_position(int pos) {
        if (head == NULL || pos < 1) {
            cout << "Invalid operation.\n";
            return;
        }

        if (pos == 1) {
            delete_from_beginning();
            return;
        }

        Node* temp = head;
        int count = 1;

        while (count < pos - 1 && temp->next != head) {
            temp = temp->next;
            count++;
        }

        if (temp->next == head || count != pos - 1) {
            cout << "Position out of bounds.\n";
            return;
        }

        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }

    // Search for a value
    void search(int val) {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        int pos = 1;
        do {
            if (temp->data == val) {
                cout << "Value " << val << " found at position " << pos << ".\n";
                return;
            }
            temp = temp->next;
            pos++;
        } while (temp != head);

        cout << "Value " << val << " not found.\n";
    }

    // Count total nodes
    int count_nodes() {
        if (head == NULL)
            return 0;

        int count = 0;
        Node* temp = head;
        do {
            count++;
            temp = temp->next;
        } while (temp != head);

        return count;
    }

    // Display the list
    void display() {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);

        cout << "(head)\n";
    }
};

// Main to test the Circular Linked List
int main() {
    CircularLinkedList clist;

    clist.insert_at_end(10);
    clist.insert_at_end(20);
    clist.insert_at_end(30);
    clist.insert_at_beginning(5);
    clist.insert_at_position(15, 3);  // Insert 15 at position 3

    cout << "List after insertions:\n";
    clist.display();

    clist.delete_from_beginning();
    clist.delete_from_end();
    clist.delete_from_position(2);

    cout << "\nList after deletions:\n";
    clist.display();

    // Searching
    clist.search(15);
    clist.search(100);

    // Count nodes
    cout << "\nTotal nodes: " << clist.count_nodes() << endl;

    return 0;
}
