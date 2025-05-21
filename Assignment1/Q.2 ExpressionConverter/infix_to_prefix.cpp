#include <iostream>
#include <fstream>
#include "stack.h"  // Custom stack implementation

using namespace std;

// Convert infix to postfix expression
string infixToPostfix(string infix) {
    Stack<char> stack;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        // If character is a letter or digit (operand)
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            postfix += ch;
        }
        // If character is opening bracket
        else if (ch == '(') {
            stack.push(ch);
        }
        // If character is closing bracket
        else if (ch == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
            }
            stack.pop(); // Remove '(' from the stack
        }
        // If character is operator
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            while (!stack.isEmpty()) {
                char top = stack.peek();
                int prec1 = (ch == '^') ? 3 : (ch == '*' || ch == '/') ? 2 : 1;
                int prec2 = (top == '^') ? 3 : (top == '*' || top == '/') ? 2 : (top == '+' || top == '-') ? 1 : 0;

                if (prec2 >= prec1) {
                    postfix += stack.pop();
                } else {
                    break;
                }
            }
            stack.push(ch);
        }
    }

    // Pop all remaining operators from the stack
    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }

    return postfix;
}

int main() {
    ifstream infile("infix.txt");   // Read input from file
    ofstream outfile("postfix.txt"); // Write output to file

    if (!infile || !outfile) {
        cout << "Error opening files!" << endl;
        return 1;
    }

    string infixExp;
    getline(infile, infixExp); // Read the infix expression from file

    string postfixExp = infixToPostfix(infixExp); // Convert it

    outfile << postfixExp; // Write result to file

    cout << "Conversion successful. Check postfix.txt" << endl;

    infile.close();
    outfile.close();

    return 0;
}
