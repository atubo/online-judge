// https://www.luogu.org/problemnew/show/P1822
// 魔法指纹

#include <bits/stdc++.h>
using namespace std;

int A, B;
int ans;
int MAXL;

void dfs2(const string &s, int pos, string &t, vector<string> &ret) {
    if (pos == -1) {
        if (t[0] != '0') ret.push_back(t);
        return;
    }
    int d = t[pos+1] - '0';
    int x = s[pos] - '0';
    if (d + x < 10) {
        t[pos] = d + x + '0';
        dfs2(s, pos-1, t, ret);
    }
    if (d - x >= 0 && x != 0) {
        t[pos] = d - x + '0';
        dfs2(s, pos-1, t, ret);
    }
}

vector<string> build(int d, const string &s) {
    const int n = s.length();
    vector<string> ret;
    string t(n+1, ' ');
    t[n] = d + '0';
    dfs2(s, n-1, t, ret);
    return ret;
}

void dfs(const string &s) {
    if ((int)s.length() > MAXL) return;
    int64_t x = stoll(s);
    if (A <= x && x <= B && s[0] != '0') {
        ans++;
    }
    if (x >= B) return;
    string l0 = "0" + s;
    for (int d = 0; d < 10; d++) {
        auto v = build(d, s);
        for (const string &t : v) {
            dfs(t);
        }
    }
    dfs(l0);
}

int main() {
    scanf("%d%d", &A, &B);
    MAXL = to_string(B).length();
    dfs("7");
    printf("%d\n", ans);
    return 0;
}
