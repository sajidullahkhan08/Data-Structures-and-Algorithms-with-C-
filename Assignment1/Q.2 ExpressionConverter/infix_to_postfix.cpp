#include <iostream>
#include <fstream>
#include "stack.h" 
using namespace std;

// Check if character is an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Get operator precedence
int precedence(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

// Convert infix expression to postfix
string infixToPostfix(string& infix) {
    Stack<char> stack;  // Using custom stack
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            postfix += ch; // Operand
        }
        else if (ch == '(') {
            stack.push(ch);
        }
        else if (ch == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
            }
            stack.pop(); // Pop the '('
        }
        else if (isOperator(ch)) {
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
                postfix += stack.pop();
            }
            stack.push(ch);
        }
    }

    // Pop remaining operators
    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }

    return postfix;
}

int main() {
    ifstream infile("infix.txt");
    ofstream outfile("postfix.txt");

    if (!infile || !outfile) {
        cout << "File error!" << endl;
        return 1;
    }

    string infixExp;
    getline(infile, infixExp); // Read input from file

    string postfixExp = infixToPostfix(infixExp);

    outfile << postfixExp;
    cout << "Conversion done. Check postfix.txt\n";

    infile.close();
    outfile.close();

    return 0;
}
