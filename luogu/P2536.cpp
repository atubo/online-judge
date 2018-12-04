// https://www.luogu.org/problemnew/show/P2536
// [AHOI2005]病毒检测

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
int curr_id;
int L;
string pattern;
bitset<1001> vis[MAXN];
int ch[MAXN][4];
int mark[MAXN];

class Trie {
public:
    Trie() {}

    void add(const string &s) {
        int curr = root_;
        for (char c: s) {
            int x = toint(c);
            if (!ch[curr][x]) {
                ch[curr][x] = ++cnt_;
            }
            curr = ch[curr][x];
        }
        mark[curr]++;
    }

    int solve() {
        dfs(root_, 0);
        return ans_;
    }

private:
    int root_ = 0;
    int cnt_ = 0;
    int ans_ = 0;

    int toint(char c) {
        if (c == 'A') return 0;
        if (c == 'C') return 1;
        if (c == 'T') return 2;
        return 3;
    }

    void dfs(int curr, int t) {
        if (t == L) {
            if (mark[curr]) {
                ans_ += mark[curr];
                mark[curr] = 0;
            }
            return;
        }
        if (vis[curr][t]) return;
        vis[curr][t] = true;
        if (pattern[t] == '*') {
            dfs(curr, t+1);
            for (int i = 0; i < 4; i++) {
                if (ch[curr][i]) dfs(ch[curr][i], t);
            }
        } else if (pattern[t] == '?') {
            for (int i = 0; i < 4; i++) {
                if (ch[curr][i]) dfs(ch[curr][i], t+1);
            }
        } else {
            int x = toint(pattern[t]);
            if (ch[curr][x]) dfs(ch[curr][x], t+1);
        }
    }
};

int main() {
    cin >> pattern;
    L = pattern.length();
    int n;
    cin >> n;
    Trie trie;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        trie.add(s);
    }
    int ret = n - trie.solve();
    printf("%d\n", ret);
    return 0;
}
