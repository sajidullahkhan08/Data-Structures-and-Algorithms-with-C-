// Hash Table with Separate Chaining
#include <iostream>
#include <cstring>
using namespace std;

// Node for key-value pair
struct PairNode {
    int key;
    char value[50];
    PairNode* next;

    PairNode(int k, const char* val) {
        key = k;
        strcpy(value, val);
        next = nullptr;
    }
};

// Hash Table class
class HashTable {
private:
    int size;
    PairNode** table; // Array of pointers to linked lists

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTable(int s) {
        size = s;
        table = new PairNode*[size];
        for (int i = 0; i < size; i++)
            table[i] = nullptr;
    }

    void insert(int key, const char* value) {
        int index = hashFunction(key);
        PairNode* head = table[index];

        // Check if key exists — update
        while (head) {
            if (head->key == key) {
                strcpy(head->value, value);
                cout << "Updated existing key.\n";
                return;
            }
            head = head->next;
        }

        // Insert new at head
        PairNode* newNode = new PairNode(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        cout << "Inserted successfully.\n";
    }

    void search(int key) {
        int index = hashFunction(key);
        PairNode* head = table[index];

        while (head) {
            if (head->key == key) {
                cout << "Found: Key = " << head->key << ", Value = " << head->value << endl;
                return;
            }
            head = head->next;
        }
        cout << "Key not found.\n";
    }

    void deleteKey(int key) {
        int index = hashFunction(key);
        PairNode* head = table[index];
        PairNode* prev = nullptr;

        while (head) {
            if (head->key == key) {
                if (prev == nullptr)
                    table[index] = head->next;
                else
                    prev->next = head->next;

                delete head;
                cout << "Deleted successfully.\n";
                return;
            }
            prev = head;
            head = head->next;
        }
        cout << "Key not found.\n";
    }

    void display() {
        cout << "\n--- Hash Table Contents ---\n";
        for (int i = 0; i < size; ++i) {
            cout << "Bucket " << i << ": ";
            PairNode* head = table[i];
            while (head) {
                cout << "(" << head->key << ", " << head->value << ") -> ";
                head = head->next;
            }
            cout << "NULL\n";
        }
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            PairNode* head = table[i];
            while (head) {
                PairNode* temp = head;
                head = head->next;
                delete temp;
            }
        }
        delete[] table;
    }
};

int main() {
    int size;
    cout << "Enter table size: ";
    cin >> size;
    HashTable ht(size);

    int choice, key;
    char value[50];

    do {
        cout << "\n===== Hash Table Menu =====\n";
        cout << "1. Insert\n2. Search\n3. Delete\n4. Display Table\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key (int): "; cin >> key;
                cout << "Enter value (string): "; cin.ignore(); cin.getline(value, 50);
                ht.insert(key, value);
                break;

            case 2:
                cout << "Enter key to search: "; cin >> key;
                ht.search(key);
                break;

            case 3:
                cout << "Enter key to delete: "; cin >> key;
                ht.deleteKey(key);
                break;

            case 4:
                ht.display();
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
