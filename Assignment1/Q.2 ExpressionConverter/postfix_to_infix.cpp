#include <iostream>
#include <fstream>  // For reading/writing files
#include <string>
#include "stack.h"  // Custom stack that supports push/pop/peek

using namespace std;

// Function to convert postfix to infix
string postfixToInfix(string postfix) {
    Stack<string> stack;

    // Loop through each character in the postfix string
    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        // If the character is an operand (letter or digit)
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            string operand(1, ch);  // Convert char to string
            stack.push(operand);    // Push operand to stack
        } 
        // If the character is an operator
        else {
            string right = stack.pop();  // Operand 2
            string left = stack.pop();   // Operand 1

            string expr = "(" + left + ch + right + ")";
            stack.push(expr); // Push the complete expression back
        }
    }

    return stack.pop(); // Final infix expression
}

int main() {
    ifstream infile("postfix.txt");     // File containing postfix expression
    ofstream outfile("infix1.txt");     // Output file for infix result

    if (!infile || !outfile) {
        cout << "Error: Could not open file!" << endl;
        return 1;
    }

    string postfixExp;
    getline(infile, postfixExp);            // Read postfix expression from file

    string infixExp = postfixToInfix(postfixExp); // Convert

    outfile << infixExp;                    // Write result to output file

    cout << "Postfix to Infix conversion completed.\n";

    infile.close();
    outfile.close();

    return 0;
}
