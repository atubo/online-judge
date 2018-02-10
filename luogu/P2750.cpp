// https://www.luogu.org/problemnew/show/P2750
// [USACO5.5]贰五语言Two Five

#include <bits/stdc++.h>
using namespace std;

char s[30];
int dp[6][6][6][6][6];

bool check(int i, int x) {
    return (!s[i] || s[i] == x + 'A');
}

int dfs(int a, int b, int c, int d, int e, int now) {
    if (now == 25) return 1;
    if (dp[a][b][c][d][e]) return dp[a][b][c][d][e];
    int &ret = dp[a][b][c][d][e];
    if (a < 5 && check(a, now)) ret += dfs(a+1, b, c, d, e, now+1);
    if (b < a && check(b+5, now)) ret += dfs(a, b+1, c, d, e, now+1);
    if (c < b && check(c+10, now)) ret += dfs(a, b, c+1, d, e, now+1);
    if (d < c && check(d+15, now)) ret += dfs(a, b, c, d+1, e, now+1);
    if (e < d && check(e+20, now)) ret += dfs(a, b, c, d, e+1, now+1);
    return ret;
}

void decode(int n) {
    for (int i = 0; i < 25; i++) {
        for (s[i] = 'A'; ; s[i]++) {
            memset(dp, 0, sizeof(dp));
            int tmp = dfs(0, 0, 0, 0, 0, 0);
            if (tmp > n) break;
            n -= tmp;
        }
    }
    printf("%s\n", s);
}

void encode(char *t) {
    int ans = 0;
    for (int i = 0; i < 25; i++) {
        for (char c = 'A'; c < t[i]; c++) {
            memset(dp, 0, sizeof(dp));
            s[i] = c;
            ans += dfs(0, 0, 0, 0, 0, 0);
        }
        s[i] = t[i];
    }
    printf("%d\n", ans + 1);
}

int main() {
    char cmd[10];
    scanf("%s", cmd);
    if (cmd[0] == 'N') {
        int x;
        scanf("%d", &x);
        decode(x-1);
    } else {
        char t[30];
        scanf("%s", t);
        encode(t);
    }

    return 0;
}
