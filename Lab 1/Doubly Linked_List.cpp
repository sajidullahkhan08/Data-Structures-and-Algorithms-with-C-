#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int val) {
        data = val;
        prev = NULL;
        next = NULL;
    }
};

// Doubly Linked List class
class DoublyLinkedList {
    Node* head;

public:
    DoublyLinkedList() {
        head = NULL;
    }

    // Insert at beginning
    void insert_at_beginning(int val) {
        Node* newNode = new Node(val);
        if (head != NULL) {
            newNode->next = head;
            head->prev = newNode;
        }
        head = newNode;
    }

    // Insert at end
    void insert_at_end(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->prev = temp;
    }

    // Insert at specific position (1-based index)
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
        while (temp != NULL && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == NULL) {
            cout << "Position out of bounds.\n";
            return;
        }

        Node* newNode = new Node(val);
        newNode->next = temp->next;
        newNode->prev = temp;

        if (temp->next != NULL)
            temp->next->prev = newNode;

        temp->next = newNode;
    }

    // Delete from beginning
    void delete_from_beginning() {
        if (head == NULL) {
            cout << "List is already empty.\n";
            return;
        }

        Node* temp = head;
        head = head->next;
        if (head != NULL)
            head->prev = NULL;
        delete temp;
    }

    // Delete from end
    void delete_from_end() {
        if (head == NULL) {
            cout << "List is already empty.\n";
            return;
        }

        if (head->next == NULL) {
            delete head;
            head = NULL;
            return;
        }

        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->prev->next = NULL;
        delete temp;
    }

    // Delete from specific position (1-based index)
    void delete_from_position(int pos) {
        if (pos < 1 || head == NULL) {
            cout << "Invalid position or empty list.\n";
            return;
        }

        if (pos == 1) {
            delete_from_beginning();
            return;
        }

        Node* temp = head;
        int count = 1;
        while (temp != NULL && count < pos) {
            temp = temp->next;
            count++;
        }

        if (temp == NULL) {
            cout << "Position out of bounds.\n";
            return;
        }

        if (temp->prev != NULL)
            temp->prev->next = temp->next;

        if (temp->next != NULL)
            temp->next->prev = temp->prev;

        delete temp;
    }

    // Search for a value
    void search(int val) {
        Node* temp = head;
        int pos = 1;
        while (temp != NULL) {
            if (temp->data == val) {
                cout << "Value " << val << " found at position " << pos << ".\n";
                return;
            }
            temp = temp->next;
            pos++;
        }
        cout << "Value " << val << " not found in the list.\n";
    }

    // Count total nodes
    int count_nodes() {
        Node* temp = head;
        int count = 0;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // Display the list forward
    void display_forward() {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // Display the list in reverse
    void display_reverse() {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }

        while (temp != NULL) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL\n";
    }
};

// Main function to test all operations
int main() {
    DoublyLinkedList list;

    // Insert operations
    list.insert_at_beginning(10);
    list.insert_at_end(20);
    list.insert_at_end(30);
    list.insert_at_position(25, 3); // Insert 25 at position 3
    list.insert_at_position(5, 1);  // Insert 5 at beginning

    cout << "List after insertions:\n";
    list.display_forward();

    // Delete operations
    list.delete_from_beginning();
    list.delete_from_end();
    list.delete_from_position(2);

    cout << "\nList after deletions:\n";
    list.display_forward();

    // Search
    list.search(25);
    list.search(100);

    // Count nodes
    cout << "\nTotal nodes in the list: " << list.count_nodes() << "\n";

    // Display reverse
    cout << "List in reverse:\n";
    list.display_reverse();

    return 0;
}
