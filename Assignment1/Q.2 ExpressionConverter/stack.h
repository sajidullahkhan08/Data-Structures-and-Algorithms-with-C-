#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T val) {
        data = val;
        next = nullptr;
    }
};

template <typename T>
class Stack {
private:
    Node<T>* top;
public:
    Stack() { top = nullptr; }
    
    bool isEmpty() { return top == nullptr; }

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
    }

    T pop() {
        if (isEmpty()) throw runtime_error("Stack underflow");
        Node<T>* temp = top;
        T value = temp->data;
        top = top->next;
        delete temp;
        return value;
    }

    T peek() {
        if (isEmpty()) throw runtime_error("Stack is empty");
        return top->data;
    }
};

#endif
