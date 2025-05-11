// Hash Table using Open Addressing (Linear Probing)
#include <iostream>
#include <cstring>
using namespace std;

// Structure for each entry in hash table
struct Entry {
    int key;
    char value[50];
    bool isOccupied;
    bool isDeleted;

    Entry() {
        key = -1;
        value[0] = '\0';
        isOccupied = false;
        isDeleted = false;
    }
};

class OpenAddressingHashTable {
private:
    int size;
    Entry* table;

    int hashFunction(int key) {
        return key % size;
    }

public:
    OpenAddressingHashTable(int s) {
        size = s;
        table = new Entry[size];
    }

    void insert(int key, const char* value) {
        int index = hashFunction(key);
        int start = index;

        do {
            if (!table[index].isOccupied || table[index].isDeleted) {
                table[index].key = key;
                strcpy(table[index].value, value);
                table[index].isOccupied = true;
                table[index].isDeleted = false;
                cout << "Inserted successfully.\n";
                return;
            } else if (table[index].isOccupied && table[index].key == key) {
                strcpy(table[index].value, value);
                cout << "Updated existing key.\n";
                return;
            }
            index = (index + 1) % size;
        } while (index != start);

        cout << "Hash table is full.\n";
    }

    void search(int key) {
        int index = hashFunction(key);
        int start = index;

        do {
            if (table[index].isOccupied && table[index].key == key && !table[index].isDeleted) {
                cout << "Found: Key = " << table[index].key << ", Value = " << table[index].value << endl;
                return;
            } else if (!table[index].isOccupied && !table[index].isDeleted) {
                break;
            }
            index = (index + 1) % size;
        } while (index != start);

        cout << "Key not found.\n";
    }

    void deleteKey(int key) {
        int index = hashFunction(key);
        int start = index;

        do {
            if (table[index].isOccupied && table[index].key == key && !table[index].isDeleted) {
                table[index].isDeleted = true;
                cout << "Deleted successfully.\n";
                return;
            } else if (!table[index].isOccupied && !table[index].isDeleted) {
                break;
            }
            index = (index + 1) % size;
        } while (index != start);

        cout << "Key not found.\n";
    }

    void display() {
        cout << "\n--- Hash Table (Open Addressing) ---\n";
        for (int i = 0; i < size; ++i) {
            cout << "Slot " << i << ": ";
            if (table[i].isOccupied && !table[i].isDeleted)
                cout << "(" << table[i].key << ", " << table[i].value << ")";
            else
                cout << "Empty";
            cout << endl;
        }
    }

    ~OpenAddressingHashTable() {
        delete[] table;
    }
};

int main() {
    int size;
    cout << "Enter table size: ";
    cin >> size;
    OpenAddressingHashTable ht(size);

    int choice, key;
    char value[50];

    do {
        cout << "\n===== Hash Table Menu (Open Addressing) =====\n";
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
