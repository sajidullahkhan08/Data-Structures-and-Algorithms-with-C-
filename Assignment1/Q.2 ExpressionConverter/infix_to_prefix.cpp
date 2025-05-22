#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

bool isOperand(char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}
int precedence(char op){
    if(op=='^') return 3;
    if(op=='*' || op=='/') return 2;
    if(op=='+' || op=='-') return 1;
    return 0; }

string reverseString(string& str) {
    string rev = "";
    for (int i = str.length() - 1; i >= 0; i--) {
        rev += str[i];
    }
    return rev;
}

string infixToPrefix(string infix) {
    infix = reverseString(infix);

    for (int i = 0; i < infix.length(); i++){
        if(infix[i] =='(')
            infix[i] = ')';
        else if(infix[i] ==')')
            infix[i] ='(';
    }
    Stack<char> stack;
    string postfix = "";
    for (char ch : infix){
        if(isOperand(ch)){
            postfix += ch;
        }
        else if(ch=='('){
            stack.push(ch);
        }
        else if (ch ==')'){
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
            }
            if (!stack.isEmpty()) stack.pop();
        }
        else {
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
                postfix += stack.pop();
            }
            stack.push(ch);
        }
    }
    while (!stack.isEmpty()) {
        postfix += stack.pop(); 
    }
    string prefix = reverseString(postfix);
    return prefix;
}

int main(){
    ifstream infile("infix.txt");
    ofstream outfile("prefix.txt");

    if (!infile || !outfile) {
        cout << "Error in   opening files!"<<endl;
        return 1;
    }
    string infixExp;
    getline(infile, infixExp);
    string prefixExp = infixToPrefix(infixExp);
    outfile << prefixExp;
    cout << "Conversion successful. Check prefix.txt" << endl;
    infile.close();
    outfile.close();
    return 0;
}
