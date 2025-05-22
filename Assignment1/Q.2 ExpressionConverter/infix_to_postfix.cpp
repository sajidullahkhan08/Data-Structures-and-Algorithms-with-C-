#include <iostream>
#include <fstream>
#include "stack.h" 
using namespace std;

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}
int precedence(char ch){
    if(ch =='^') return 3;
    if(ch =='*' || ch =='/') return 2;
    if(ch =='+' || ch == '-') return 1;
    return 0;
}

string infixToPostfix(string& infix) {
    Stack<char> stack;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++){
        char ch = infix[i];
        if((ch >='a' && ch <='z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            postfix += ch;
        }
        else if(ch == '('){
            stack.push(ch);
        }
        else if(ch == ')'){
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
            }
            stack.pop();
        }
        else if(isOperator(ch)){
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
                postfix += stack.pop();
            }
            stack.push(ch);
        }
    }
    while(!stack.isEmpty()){
        postfix += stack.pop();
    }
    return postfix;
}

int main() {
    ifstream infile("infix.txt");
    ofstream outfile("postfix.txt");

    if (!infile || !outfile){
        cout << "there is file error!" << endl;
        return 1;
    }
    string infixExp;
    getline(infile, infixExp);
    string postfixExp = infixToPostfix(infixExp);
    outfile << postfixExp;
    cout << "Conversion done. Check postfix.txt\n";
    infile.close();
    outfile.close();

    return 0;
}
