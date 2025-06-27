#include <iostream>
#include <stack>
#include <string>
using namespace std;

string reverseString(string s) {
    stack<char> st;
    for (char c : s)
        st.push(c);

    string reversed = "";
    while (!st.empty()) {
        reversed += st.top();
        st.pop();
    }
    return reversed;
}

int main() {
    string s = "hello";
    cout << "Reversed: " << reverseString(s);
    return 0;
}
