// https://www.luogu.org/problemnew/show/P3417
// [POI2005]BANK-Cash Dispenser

#include <bits/stdc++.h>
using namespace std;

int N;
int nxt[10][10010];
bool mark[10000];

void build(const string &s) {
    const int l = s.length();
    for (int i = l-1; i >= 0; i--) {
        int x = s[i] - '0';
        for (int d = 0; d < 10; d++) nxt[d][i] = nxt[d][i+1];
        nxt[x][i] = i;
    }
}

bool check(int x0) {
    int d[4];
    int x = x0;
    for (int i = 0; i < 4; i++) {
        d[i] = x % 10;
        x /= 10;
    }
    int p = 0;
    for (int i = 3; i >= 0; i--) {
        x = d[i];
        p = nxt[x][p];
        if (p == -1) return false;
    }
    return true;
}

void solve() {
    int t;
    scanf("%d", &t);
    string s;
    cin >> s;
    for (int i = 0; i < 10; i++) {
        memset(nxt[i], -1, (t+1)*sizeof(int));
    }
    build(s);

    for (int x = 0; x < 10000; x++) {
        if (!check(x)) mark[x] = true;
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        solve();
    }
    int ans = 0;
    for (int x = 0; x < 10000; x++) {
        if (!mark[x]) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
