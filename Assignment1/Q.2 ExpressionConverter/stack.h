#ifndef STACK_H // ifndef is used for preprocessor directives to prevent multiple inclusions of the same header file
#define STACK_H // This is a header guard to prevent multiple inclusions of this header file

#include <iostream>
using namespace std;

template <typename T> // Template class to allow for different data types, template<typename T> allows the class to be used with any data type
class Node {
public:
    T data; // T is the data type of the node
    Node* next;
    Node(T val) {
        data = val;
        next = nullptr;
    }
};

template <typename T>
class Stack {
private:
    Node<T>* top; // <T> indicates that top is a pointer to a Node of type T
public:
    Stack() { top = nullptr; }
    
    bool isEmpty() { return top == nullptr; }

    void push(T value) {
        Node<T>* newNode = new Node<T>(value); // Create a new node with the given value (T value)
        newNode->next = top; // Link the new node to the previous top
        top = newNode; // Update top to the new node
    }

    T pop() {
        if (isEmpty()) throw runtime_error("Stack underflow"); // If the stack is empty, throw an exception
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

#endif // it is used to end the header guard
// This prevents the header file from being included multiple times in a single translation unit, which can cause redefinition errors.
