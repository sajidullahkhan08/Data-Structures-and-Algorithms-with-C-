#include <iostream>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
};

DNode* insertAtHead(DNode* head, int val) {
    DNode* newNode = new DNode();
    newNode->data = val;
    newNode->prev = NULL;
    newNode->next = head;
    if (head != NULL)
        head->prev = newNode;
    return newNode;
}

DNode* insertAtTail(DNode* head, int val) {
    DNode* newNode = new DNode();
    newNode->data = val;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        return newNode;
    }

    DNode* temp = head;
    while (temp->next != NULL) temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

void printForward(DNode* head) {
    while (head != NULL) {
        cout << head->data << " <-> ";
        head = head->next;
    }
    cout << "NULL\n";
}

int main() {
    DNode* head = NULL;

    head = insertAtHead(head, 30);
    head = insertAtHead(head, 20);
    head = insertAtTail(head, 40);

    printForward(head);

    return 0;
}
