// http://codeforces.com/problemset/problem/610/C

#include <bits/stdc++.h>

using namespace std;

const vector<char> CHARS = {'*', 'X', '+'};

vector<char> build(const vector<char>& v, int f) {
    vector<char> ret = v;
    for (char c: v) {
        ret.push_back(c * f);
    }
    return ret;
}

vector<vector<char>> solve(int k) {
    if (k == 0) return {{1}};
    vector<vector<char>> ret;
    vector<vector<char>>  prev = solve(k-1);
    for (const auto& v: prev) {
        ret.push_back(build(v, 1));
        ret.push_back(build(v, -1));
    }
    return ret;
}

void output(const vector<vector<char>>& m) {
    for (const auto& v: m) {
        for (char c: v) {
            printf("%c", CHARS[c+1]);
        }
        printf("\n");
    }
}

int main() {
    int k;
    cin >> k;
    auto ret = solve(k);
    output(ret);
    return 0;
}
