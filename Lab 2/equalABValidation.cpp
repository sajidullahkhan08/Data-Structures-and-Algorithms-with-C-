#include <iostream>
#include <string>
using namespace std;

// implementation of equal no of a's and b's using stack
class ArrayStack {
private:
    int top;
    int size;
    char* arr;

public:
    ArrayStack(int n) {
        size = n;
        top = -1;
        arr = new char[size];
    }

    ~ArrayStack() { // Destructor to free memory
        delete[] arr;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == size - 1;
    }

    void push(char data) {
        if (!isFull()) {
            arr[++top] = data;
        } else {
            cout << "Stack Overflow" << endl;
        }
    }

    void pop() {
        if (!isEmpty()) {
            top--;
        } else {
            cout << "Stack Underflow" << endl;
        }
    }

    // Stack-based check for equal 'a' and 'b' occurrences
    bool checkABEqual(const string& str) {
        for (size_t i = 0; i < str.length(); i++) {
            char ch = str[i];
            if (ch == 'a') {
                push('a'); // Push 'a' onto the stack
            } else if (ch == 'b') {
                if (!isEmpty()) {
                    pop(); // Cancel one 'a' with a 'b'
                } else {
                    push('b'); // Push 'b' if there's no 'a' to match
                }
            }
        }

        return isEmpty(); // Stack should be empty if a's and b's are balanced
    }
};

int main() {
    ArrayStack s(100); // Large enough stack for testing

    cout << s.checkABEqual("aabb") << endl;       // 1 (true)
    cout << s.checkABEqual("aaaabbbb") << endl;   // 1 (true)
    cout << s.checkABEqual("abba") << endl;       // 1 (true)
    cout << s.checkABEqual("baba") << endl;       // 1 (true)
    cout << s.checkABEqual("bbbaaa") << endl;     // 1 (true)
    cout << s.checkABEqual("abb") << endl;        // 0 (false)
    cout << s.checkABEqual("aaab") << endl;       // 0 (false)
    cout << s.checkABEqual("abbbbb") << endl;     // 0 (false)

    return 0;
}