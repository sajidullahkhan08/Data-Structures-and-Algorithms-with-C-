#include <iostream>
#include <cstring>
using namespace std;

class Stack {
public:
    char arr[100];
    int top;

    Stack() {
        top = -1;
    }

    void push(char ch) {
        arr[++top] = ch;
    }

    char pop() {
        return arr[top--];
    }

    char peek() {
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

int getPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void reverseAndSwap(char expr[]) {
    int len = strlen(expr);
    for (int i = 0; i < len / 2; i++) {
        char temp = expr[i];
        expr[i] = expr[len - i - 1];
        expr[len - i - 1] = temp;
    }

    // Swap '(' and ')'
    for (int i = 0; i < len; i++) {
        if (expr[i] == '(') expr[i] = ')';
        else if (expr[i] == ')') expr[i] = '(';
    }
}

void infixToPrefix(char infix[]) {
    reverseAndSwap(infix);

    Stack s;
    char prefix[100];
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (ch >= 'a' && ch <= 'z') {
            prefix[j++] = ch;
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                prefix[j++] = s.pop();
            }
            s.pop();
        } else if (isOperator(ch)) {
            while (!s.isEmpty() && getPrecedence(s.peek()) > getPrecedence(ch)) {
                prefix[j++] = s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.isEmpty()) {
        prefix[j++] = s.pop();
    }

    prefix[j] = '\0';
    reverseAndSwap(prefix);

    cout << "Prefix: " << prefix << endl;
}

int main() {
    char infix[100];
    cout << "Enter infix expression: ";
    cin >> infix;

    infixToPrefix(infix);

    return 0;
}
