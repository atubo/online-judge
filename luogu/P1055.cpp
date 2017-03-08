// https://www.luogu.org/problem/show?pid=1055
// ISBN号码

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int d = 0, f = 1;
    for (int i = 0; i <= 10; i++) {
        if (s[i] == '-') continue;
        d = (d + (s[i] - '0') * (f++)) % 11;
    }
    string e = s;
    e.back() = (d == 10 ? 'X' : '0' + d);
    if (e == s) {
        cout << "Right" << endl;
    } else {
        cout << e << endl;
    }
    return 0;
}
