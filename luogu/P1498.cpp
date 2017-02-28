// https://www.luogu.org/problem/show?pid=1498
// 南蛮图腾

#include <bits/stdc++.h>
using namespace std;

const vector<string> UNIT = {" /\\ ", "/__\\"};

vector<string> build(int n) {
    if (n == 1) return UNIT;
    vector<string> gprev = build(n-1);
    vector<string> g;
    string SHIFT(1<<(n-1), ' ');
    for (const string& s: gprev) {
        g.push_back(SHIFT + s + SHIFT);
    }
    for (const string& s: gprev) {
        g.push_back(s + s);
    }
    return g;
}

int main() {
    int n;
    cin >> n;
    vector<string> g = build(n);
    for (const string& s: g) {
        cout << s << endl;
    }
    return 0;
}
