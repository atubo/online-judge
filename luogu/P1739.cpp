// https://www.luogu.org/problem/show?pid=1739
// 表达式括号匹配
#include <iostream>
#include <stack>
using namespace std;

bool solve(const string& s) {
    int left = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] == '(') left++;
        else if (s[i] == ')') {
            left--;
            if (left < 0) return false;
        }
    }
    return left == 0;
}

int main() {
    string s;
    cin >> s;
    cout << (solve(s) ? "YES" : "NO") << endl;
    return 0;
}
