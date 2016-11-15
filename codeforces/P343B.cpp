// http://codeforces.com/problemset/problem/343/B

#include <iostream>
#include <stack>

using namespace std;

int main() {
    string s;
    cin >> s;
    stack<char> st;
    for (char c: s) {
        if (!st.empty() && c == st.top()) {
            st.pop();
        } else {
            st.push(c);
        }
    }
    cout << (st.empty() ? "YES" : "NO") << endl;
    return 0;
}
