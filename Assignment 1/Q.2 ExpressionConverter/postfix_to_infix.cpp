#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

// Function to convert postfix to infix
string postfixToInfix(string postfix) {
    Stack<string> stack;

    for (char ch : postfix) {
        if (isalnum(ch)) {
            stack.push(string(1, ch));
        } else {
            string op2 = stack.pop();
            string op1 = stack.pop();
            string expression = "(" + op1 + ch + op2 + ")";
            stack.push(expression);
        }
    }

    return stack.pop();
}

int main() {
    string postfixExp;
    ifstream infile("postfix.txt");
    ofstream outfile("infix1.txt");

    if (!infile || !outfile) {
        cout << "Error opening files!" << endl;
        return 1;
    }

    getline(infile, postfixExp);
    outfile << postfixToInfix(postfixExp);

    cout << "Postfix to Infix conversion done.\n";

    infile.close();
    outfile.close();
    return 0;
}
