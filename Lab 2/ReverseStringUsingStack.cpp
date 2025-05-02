#include <iostream>
#include <stack>
using namespace std;

void reverseString(string str) {
    stack<char> s;

    for (char c : str) {
        s.push(c);
    }

    cout << "Reversed string: ";
    while (!s.empty()) {
        cout << s.top();
        s.pop();
    }
    cout << endl;
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    reverseString(input);
    return 0;
}
