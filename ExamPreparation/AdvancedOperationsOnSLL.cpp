#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* insertAtPos(Node* head, int val, int pos) {
    Node* newNode = new Node();
    newNode->data = val;

    if (pos == 0) {
        newNode->next = head;
        return newNode;
    }

    Node* temp = head;
    for (int i = 0; temp != NULL && i < pos - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) return head;

    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

Node* deleteAtPos(Node* head, int pos) {
    if (head == NULL) return NULL;

    if (pos == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    Node* temp = head;
    for (int i = 0; temp != NULL && i < pos - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) return head;

    Node* delNode = temp->next;
    temp->next = delNode->next;
    delete delNode;
    return head;
}

int search(Node* head, int key) {
    int pos = 0;
    while (head != NULL) {
        if (head->data == key) return pos;
        head = head->next;
        pos++;
    }
    return -1;
}

Node* reverse(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

void printList(Node* head) {
    while (head != NULL) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

int main() {
    Node* head = NULL;

    head = insertAtPos(head, 10, 0);
    head = insertAtPos(head, 20, 1);
    head = insertAtPos(head, 30, 2);
    printList(head); // 10 -> 20 -> 30 -> NULL

    head = deleteAtPos(head, 1);
    printList(head); // 10 -> 30 -> NULL

    cout << "Search 30 at pos: " << search(head, 30) << endl;

    head = reverse(head);
    printList(head); // 30 -> 10 -> NULL

    return 0;
}
