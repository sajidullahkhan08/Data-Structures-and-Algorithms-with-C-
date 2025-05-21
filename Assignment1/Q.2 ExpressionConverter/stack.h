#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

// Node class to store data and a pointer to the next node
template <typename T>
class Node {
public:
    T data;            // Stores value of any type
    Node* next;        // Pointer to the next node

    Node(T val) {
        data = val;
        next = nullptr;
    }
};

// Stack class using linked list
template <typename T>
class Stack {
private:
    Node<T>* top;  // Pointer to the top of the stack

public:
    Stack() {
        top = nullptr;
    }

    // Check if stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Add a value to the top of the stack
    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
    }

    // Remove and return the top value
    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty!");
        }

        Node<T>* temp = top;
        T value = temp->data;
        top = top->next;
        delete temp;

        return value;
    }

    // Return the top value without removing it
    T peek() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty!");
        }

        return top->data;
    }
};

#endif
