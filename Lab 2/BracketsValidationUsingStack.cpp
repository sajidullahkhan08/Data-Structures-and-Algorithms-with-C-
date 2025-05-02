#include <iostream>
using namespace std;

#define MAX 100

class Stack {
    char arr[MAX];
    int top;

public:
    Stack() { top = -1; }

    void push(char ch) {
        if (top < MAX - 1)
            arr[++top] = ch;
    }

    char pop() {
        if (top >= 0)
            return arr[top--];
        return '\0'; // return null character if empty
    }

    char peek() {
        if (top >= 0)
            return arr[top];
        return '\0';
    }

    bool isEmpty() {
        return top == -1;
    }
};

// Function to check if opening and closing brackets match
bool isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// Function to validate bracket expression using Stack
bool isValidBrackets(string expr) {
    Stack stack;

    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (stack.isEmpty() || !isMatching(stack.pop(), ch)) {
                return false;
            }
        }
    }

    return stack.isEmpty(); // True if all brackets matched and stack is empty
}

int main() {
    string expr;

    cout << "Enter an expression: ";
    cin >> expr;

    if (isValidBrackets(expr))
        cout << "Brackets are valid and balanced.\n";
    else
        cout << "Brackets are NOT valid or balanced!\n";

    return 0;
}
