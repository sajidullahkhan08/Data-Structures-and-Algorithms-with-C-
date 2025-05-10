#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

// Function to check if a character is an operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to get the precedence of an operator
int precedence(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

// Function to convert infix to postfix
string infixToPostfix(string infix) {
    Stack<char> stack;
    string postfix = "";

    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
            }
            stack.pop(); // Remove '(' from stack
        } else if (isOperator(ch)) {
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
                postfix += stack.pop();
            }
            stack.push(ch);
        }
    }
    
    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }

    return postfix;
}

int main() {
    string infixExp;
    ifstream infile("infix.txt");
    ofstream outfile("postfix.txt");

    if (!infile || !outfile) {
        cout << "Error opening files!" << endl;
        return 1;
    }

    getline(infile, infixExp);
    outfile << infixToPostfix(infixExp);

    cout << "Infix to Postfix conversion done.\n";

    infile.close();
    outfile.close();
    return 0;
}
