// https://www.luogu.org/problem/show?pid=1914
// 小书童——密码

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    for (int i = 0; i < (int)s.length(); i++) {
        s[i] = ((s[i] - 'a' + n) % 26) + 'a';
    }
    cout << s << endl;
    return 0;
}
