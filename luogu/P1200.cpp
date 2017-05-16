// https://www.luogu.org/problem/show?pid=1200
// [USACO1.1]你的飞碟在这儿

#include <bits/stdc++.h>
using namespace std;

int toint(const string &s) {
    int ret = 1;
    for (char c: s) {
        ret *= (c - 'A' + 1);
    }
    return ret % 47;
}

int main() {
    string s, t;
    cin >> s >> t;
    if (toint(s) == toint(t)) {
        cout << "GO" << endl;
    } else {
        cout << "STAY" << endl;
    }
    return 0;
}
