// https://www.luogu.org/problem/show?pid=1241
// 括号序列

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

int main() {
    string s;
    cin >> s;
    const int N = s.length();
    bool add[N+1] = {false};
    stack<PII> st;
    for (int i = 0; i < N; i++) {
        char c = s[i];
        switch (c) {
            case '(':
                st.push(make_pair(0, i));
                break;
            case '[':
                st.push(make_pair(1, i));
                break;
            case ')':
                if (st.empty() || st.top().first != 0) {
                    add[i] = true;
                } else {
                    st.pop();
                }
                break;
            case ']':
                if (st.empty() || st.top().first != 1) {
                    add[i] = true;
                } else {
                    st.pop();
                }
                break;
            default:
                break;
        }
    }
    while (!st.empty()) {
        add[st.top().second] = true;
        st.pop();
    }

    for (int i = 0; i < N; i++) {
        char c = s[i];
        switch (c) {
            case '(':
                cout << c;
                if (add[i]) cout << ')';
                break;
            case '[':
                cout << c;
                if (add[i]) cout << ']';
                break;
            case ')':
                if (add[i]) cout << '(';
                cout << c;
                break;
            case ']':
                if (add[i]) cout << '[';
                cout << c;
                break;
        }
    }
    cout << endl;
    return 0;
}
