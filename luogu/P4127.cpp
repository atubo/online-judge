// https://www.luogu.org/problemnew/show/P4127
// [AHOI2009]同类分布

#include <bits/stdc++.h>
using namespace std;

int64_t dp[165][20][165];
int64_t p10[20];

int64_t solve(const string &str, int s, int d, int r, bool clamp,
              int y) {
    if (d == -1) return (s == 0 && r == 0);
    if (!clamp && dp[s][d][r] != -1) return dp[s][d][r];
    if (s > (d+1) * 9) return 0;
    const int n = str.length();
    int64_t ret = 0;
    if (clamp) {
        int maxx = min(s, str[n-1-d]-'0');
        for (int x = 0; x <= maxx; x++) {
            int rn = (r - x * p10[d]) % y;
            if (rn < 0) rn += y;
            ret += solve(str, s-x, d-1, rn,
                         x == str[n-1-d]-'0', y);
        }
    } else {
        int maxx = min(s, 9);
        for (int x = 0; x <= maxx; x++) {
            int rn = (r - x * p10[d]) % y;
            if (rn < 0) rn += y;
            ret += solve(str, s-x, d-1, rn,
                         false, y);
        }
        dp[s][d][r] = ret;
    }
    return ret;
}

void init0() {
    p10[0] = 1;
    for (int i = 1; i <= 18; i++) {
        p10[i] = 10 * p10[i-1];
    }
}

void init() {
    memset(dp, -1, sizeof(dp));
}

int64_t solve(const string &str, int y) {
    init();
    const int n = str.length();
    int64_t ret = 0;
    for (int x = 1; x <= min(y, str[0]-'0'); x++) {
        ret += solve(str, y-x, n-2, ((y-x*p10[n-1]) % y + y) % y,
                     x == str[0]-'0', y);
    }
    return ret;
}

int64_t solve(const string &str) {
    const int n = str.length();
    int64_t ret = 0;
    for (int y = 1; y <= 9*n; y++) {
        ret += solve(str, y);
    }
    return ret;
}

int64_t solve1(const string &str) {
    const int n = str.length();
    int64_t ret = 0;
    for (int i = 1; i < n; i++) {
        string s(i, '9');
        ret += solve(s);
    }
    ret += solve(str);
    return ret;
}

bool check(const string &s) {
    int d = 0;
    for (char c: s) {
        d += c - '0';
    }
    return stol(s) % d == 0;
}

int main() {
    init0();
    string a, b;
    cin >> a >> b;
    int64_t ans = solve1(b) - solve1(a) + check(a);
    printf("%ld", ans);
    return 0;
}
