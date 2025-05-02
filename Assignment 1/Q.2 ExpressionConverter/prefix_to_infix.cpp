#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "stack.h"

using namespace std;

// Function to convert prefix to infix
string prefixToInfix(string prefix) {
    Stack<string> stack;
    reverse(prefix.begin(), prefix.end());

    for (char ch : prefix) {
        if (isalnum(ch)) {
            stack.push(string(1, ch));
        } else {
            string op1 = stack.pop();
            string op2 = stack.pop();
            string expression = "(" + op1 + ch + op2 + ")";
            stack.push(expression);
        }
    }

    return stack.pop();
}

int main() {
    string prefixExp;
    ifstream infile("prefix.txt");
    ofstream outfile("infix2.txt");

    if (!infile || !outfile) {
        cout << "Error opening files!" << endl;
        return 1;
    }

    getline(infile, prefixExp);
    outfile << prefixToInfix(prefixExp);

    cout << "Prefix to Infix conversion done.\n";

    infile.close();
    outfile.close();
    return 0;
}
