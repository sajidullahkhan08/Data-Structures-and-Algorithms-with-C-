#include <iostream>
#include <fstream> // For file operations
#include <string>
#include "stack.h"

using namespace std;

string reverseString(string& str){
     string rev = "";
    for (int i = str.length() - 1; i >= 0; i--){
        rev += str[i];
    }
    return rev;
}
string prefixToInfix(string prefix) {
    Stack<string> stack;
    reverseString(prefix);

    for (int i = 0; i < prefix.length(); i++) {
        char ch = prefix[i];
        if ((ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || (ch>='0' && ch<='9')) {
            string operand(1, ch);
            stack.push(operand);
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
    ifstream infile("prefix.txt");
    ofstream outfile("infix2.txt");

    if(!infile || !outfile) {
        cout << "Error in opening files!" << endl;
        return 1;
    }
    string prefixExp;
    getline(infile, prefixExp);
    string infixExp = prefixToInfix(prefixExp);
    outfile << infixExp;
    cout << "Prefix to Infix conversion done.\n";
    infile.close();
    outfile.close();
    return 0;
}
