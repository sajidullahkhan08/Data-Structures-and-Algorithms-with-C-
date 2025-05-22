#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

string postfixToInfix(string postfix) {
    Stack<string> stack;
    for(int i=0; i < postfix.length(); i++){
        char ch = postfix[i];
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            string operand(1, ch);
            stack.push(operand);
        } 
        else{
            string right = stack.pop();
            string left = stack.pop();
            string expr = "(" + left + ch + right + ")";
            stack.push(expr);
        }
    }
    return stack.pop();
}

int main() {
    ifstream infile("postfix.txt"); 
    ofstream outfile("infix1.txt");

    if(!infile || !outfile){
        cout << "Error: Could not open file!"<<endl;
        return 1;
    }
    string postfixExp;
    getline(infile, postfixExp);
    string infixExp = postfixToInfix(postfixExp);
    outfile << infixExp;
    cout << "Postfix to Infix conversion completed.\n";

    infile.close();
    outfile.close();

    return 0;
}
