// int evaluatePostfix(string exp) {
//     stack<int> st;
//     for (char ch : exp) {
//         if (isdigit(ch)) st.push(ch - '0');
//         else {
//             int b = st.top(); st.pop();
//             int a = st.top(); st.pop();
//             switch (ch) {
//                 case '+': st.push(a + b); break;
//                 case '-': st.push(a - b); break;
//                 case '*': st.push(a * b); break;
//                 case '/': st.push(a / b); break;
//             }
//         }
//     }
//     return st.top();
// }


// int evaluatePrefix(string exp) {
//     stack<int> st;
//     for (int i = exp.length() - 1; i >= 0; i--) {
//         char ch = exp[i];
//         if (isdigit(ch)) st.push(ch - '0');
//         else {
//             int a = st.top(); st.pop();
//             int b = st.top(); st.pop();
//             switch (ch) {
//                 case '+': st.push(a + b); break;
//                 case '-': st.push(a - b); break;
//                 case '*': st.push(a * b); break;
//                 case '/': st.push(a / b); break;
//             }
//         }
//     }
//     return st.top();
// }
