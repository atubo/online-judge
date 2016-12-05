// https://www.luogu.org/problem/show?pid=1449
// 后缀表达式
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int nextNumber(const string& s, int& pos) {
    int N = s.length();
    int q = pos + 1;
    for (; q < N; q++) {
        if (!isdigit(s[q])) break;
    }
    int ans = atoi(s.substr(pos, q - pos).c_str());
    pos = q + 1;
    return ans;
}

int main() {
    string s;
    cin >> s;
    int pos = 0;
    stack<int> st;
    while (true) {
        char c = s[pos];
        if (c == '@') break;
        if (isdigit(c)) {
            st.push(nextNumber(s, pos));
        } else {
            pos++;
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();
            if (c == '+') st.push(a + b);
            else if (c == '-') st.push(a - b);
            else if (c == '*') st.push(a * b);
            else {
                assert(c == '/');
                st.push(a / b);
            }
        }
    }
    assert(st.size() == 1);
    cout << st.top() << endl;
    return 0;
}
