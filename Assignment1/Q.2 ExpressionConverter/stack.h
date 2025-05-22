#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;         
    Node* next;      

    Node(T val){
        data = val;
        next = NULL;}
};

template <typename T>
class Stack {
private:
    Node<T>* top;
public:
    Stack(){
        top = NULL;
    }
    bool isEmpty(){
        return top == NULL;
    }
    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
    }
    T pop(){
        if(isEmpty()) {
            cout <<"error: Stack is empty!"<< endl;
        }
        Node<T>* temp = top;
        T value = temp->data;
        top = top->next;
        delete temp;
        return value;
    }
    T peek(){
        if(isEmpty()) {
            cout<<"error: Stack is empty!"<<endl;
        }
        return top->data;
    }
};
#endif
