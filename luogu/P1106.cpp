// https://www.luogu.org/problem/show?pid=1106
// 删数问题

#include <bits/stdc++.h>
using namespace std;

int main() {
    string A;
    int remain;
    cin >> A >> remain;
    stack<char> s;
    for (int i = 0; i < (int)A.length(); i++) {
        while (!s.empty() && s.top() > A[i] && remain > 0) {
            s.pop();
            remain--;
        }
        s.push(A[i]);
    }
    while (remain) {
        s.pop();
        remain--;
    }
    string ret;
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    while (ret.size() > 1 && ret.back() == '0') ret.pop_back();
    reverse(ret.begin(), ret.end());
    cout << ret << endl;
    return 0;
}
