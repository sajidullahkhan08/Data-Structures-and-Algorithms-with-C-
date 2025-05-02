#include <iostream>
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

void infixToPostfix(char infix[]) {
    Stack s;
    char postfix[100];
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (ch >= 'a' && ch <= 'z') {
            postfix[j++] = ch; // directly add operand
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix[j++] = s.pop();
            }
            s.pop(); // remove '('
        } else if (isOperator(ch)) {
            while (!s.isEmpty() && getPrecedence(s.peek()) >= getPrecedence(ch)) {
                postfix[j++] = s.pop();
            }
            s.push(ch);
        }
    }

    // pop remaining operators
    while (!s.isEmpty()) {
        postfix[j++] = s.pop();
    }

    postfix[j] = '\0';

    cout << "Postfix: " << postfix << endl;
}

int main() {
    char infix[100];
    cout << "Enter infix expression: ";
    cin >> infix;

    infixToPostfix(infix);

    return 0;
}