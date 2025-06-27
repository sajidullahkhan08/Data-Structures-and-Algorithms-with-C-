#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* insertAtHead(Node* head, int val) {
    Node* newNode = new Node();
    newNode->data = val;
    newNode->next = head;
    return newNode;
}

Node* insertAtTail(Node* head, int val) {
    Node* newNode = new Node();
    newNode->data = val;
    newNode->next = NULL;

    if (head == NULL) return newNode;

    Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

int main() {
    Node* head = NULL;

    head = insertAtHead(head, 30);
    head = insertAtHead(head, 20);
    head = insertAtTail(head, 40);
    printList(head);

    return 0;
}
