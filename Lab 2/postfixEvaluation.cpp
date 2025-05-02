#include <iostream>
#include <cmath>    // For pow() function
#include <cctype>   // For isdigit()
using namespace std;

class ArrayStack {
private:
    int top;
    int size;
    double* arr; // Using double for handling division results

public:
    ArrayStack(int capacity) {
        size = capacity;
        top = -1;
        arr = new double[size];
    }

    ~ArrayStack() {
        delete[] arr;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == size - 1;
    }

    void push(double data) {
        if (!isFull()) {
            arr[++top] = data;
        } else {
            cout << "Stack Overflow" << endl;
        }
    }

    double pop() {
        if (!isEmpty()) {
            return arr[top--];
        } else {
            cout << "Stack Underflow" << endl;
            return 0;
        }
    }

    double peek() {
        if (!isEmpty()) {
            return arr[top];
        } else {
            return 0;
        }
    }
};

// Function to evaluate a postfix expression
double evaluatePostfix(string postfix) {
    int n = postfix.length();
    ArrayStack stack(n);

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        // If character is a digit, push it to stack (assuming single-digit numbers)
        if (isdigit(ch)) {
            stack.push(ch - '0'); // Convert char to int
        }
        // If character is an operator, pop two operands and perform the operation
        else {
            double operand2 = stack.pop();
            double operand1 = stack.pop();
            double result = 0;

            switch (ch) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': 
                    if (operand2 == 0) {
                        cout << "Error: Division by zero" << endl;
                        return 0;
                    }
                    result = operand1 / operand2;
                    break;
                case '^': result = pow(operand1, operand2); break;
                default:
                    cout << "Error: Invalid operator" << endl;
                    return 0;
            }

            stack.push(result); // Push the result back to stack
        }
    }

    return stack.pop(); // Final result
}

// Main function
int main() {
    string postfix;
    cout << "Enter postfix expression (single-digit operands): ";
    cin >> postfix;

    double result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;

    return 0;
}
