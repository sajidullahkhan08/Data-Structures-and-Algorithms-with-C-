// #include <iostream>

// using namespace std;

// class ArrayStack {
//     private:
//         int array[10];
//         int top;
//     public:
//         ArrayStack() {
//             top = -1;
//         }

//         void push(int value) {
//             if(top == 10-1) {
//                 cout << "Stack overflow!" <<endl;
//             }
//             else {
//                 array[++top] = value;
//             }
//         }

//         int pop() {
//             if(top == -1) {
//                 cout << "Stack underflow!" <<endl;
//                 return 0;
//             }
//             else {
//                 return array[top--];
//             }
//         }

//         bool isEmpty() {
//             if(top == -1) return true;
//             else return false;
//         }
//         bool isFull() {
//             if(top == 10-1) return true;
//             else return false;
//         }

//         int Top() {
//             return array[top];
//         }
// };

// int main() {
//     ArrayStack stack;

//     stack.push(1);
//     stack.push(2);

//     cout << stack.Top();

//     while(!stack.isEmpty()) {
//         cout << stack.pop() <<endl;
//     }

//     return 0;
// }

#include<iostream>
using namespace std;
const int MAX = 100;
template <class Type>
class Stack {
private:
Type data[MAX]; // stack: array of any type
int top; // number of top of stack
public:
Stack(); // constructor
void push(Type); // put number on stack
Type pop(); // take number off stack
bool isEmpty();//checks if stack is empty or not
Type topValue();//gives top value of stack
};

template <class Type>
Stack<Type>::Stack()
{
top = -1;
}
// Push a value onto the stack
template <class Type>
void Stack<Type>::push(Type item)
{
if (top == MAX-1)
cerr << "Stack Full!\n";
else
data[++top] = item;
}

// Pop a value off of the stack
template <class Type>
Type Stack<Type>::pop()
{
if (top == -1)
{
cerr << "Stack Empty!\n";
return 0;
}
else
return data[top--];
}

// Check whether the stack is empty
template <class Type>
bool Stack<Type>::isEmpty()
{
if (top == -1)
return true;
else
return false;
}
// Provide the top value of the stack
template <class Type>
Type Stack<Type>::topValue()
{
return data[top];
}

int main()
{
// // s1 is object of class Stack<float>
// Stack<float> s1;
// // push 2 floats, pop 2 floats
// s1.push(11.1);
// s1.push(22.2);
// s1.push(33.3);
// cout << "1: " << s1.pop() << endl;
// cout << "2: " << s1.pop() << endl;
// while (!s1.isEmpty())
// {cout <<"from loop: " << s1.pop() <<endl;}
// s2 is object of class Stack<int>
Stack<int> s2;
// push 2 ints, pop 2 ints
s2.push(123);
s2.push(456);
cout << "1: " << s2.pop() << endl;
cout << "2: " << s2.pop() << endl;
return 0;
}