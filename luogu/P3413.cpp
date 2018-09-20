// https://www.luogu.org/problemnew/show/P3413
// SAC#1 - 萌数

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int dp[10][10][1010];
int base[1010];

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int sub(int64_t a, int64_t b) {
    return ((a - b) % MOD + MOD) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int solve(int p1, int p2, bool clamped, const string &s, int d) {
    const int n = s.length();
    if (d == -1) return 1;
    if (!clamped && dp[p1][p2][d] != -1) return dp[p1][p2][d];
    int ret = 0;
    if (clamped) {
        int x = 0;
        for (; x < s[n-1-d]-'0'; x++) {
            if (x == p1 || x == p2) continue;
            ret = add(ret, solve(p2, x, false, s, d-1));
        }
        if (x != p1 && x != p2) {
            ret = add(ret, solve(p2, x, true, s, d-1));
        }
    } else {
        for (int x = 0; x < 10; x++) {
            if (x == p1 || x == p2) continue;
            ret = add(ret, solve(p2, x, false, s, d-1));
        }
        dp[p1][p2][d] = ret;
    }
    return ret;
}

int solve(const string &s) {
    const int n = s.length();
    if (n == 1) return stoi(s);
    int x0 = stoi(s.substr(0, 2));
    int ans = 0;
    for (int x = 10; x < x0; x++) {
        int p1 = x/10, p2 = x%10;
        if (p1 == p2) continue;
        ans = add(ans, solve(p1, p2, false, s, n-3));
    }
    if (x0/10 != x0%10) {
    ans = add(ans, solve(x0/10, x0%10, true, s, n-3));
    }
    return ans;
}

void init() {
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= 1000; i++) {
        string s(i, '9');
        base[i] = solve(s);
    }
}

int countCute(const string &s) {
    int uncute = solve(s);
    for (int i = 1; i <= (int)s.length()-1; i++) {
        uncute = add(uncute, base[i]);
    }
    int tot = 0;
    for (char c: s) {
        tot = add(mul(tot, 10), c-'0');
    }
    return sub(tot, uncute);
}

bool isCute(const string &s) {
    const int n = s.length();
    if (n < 2) return false;
    if (s[1] == s[0]) return true;
    for (int i = 2; i < n; i++) {
        if (s[i] == s[i-1] || s[i] == s[i-2]) return true;
    }
    return false;
}

string L, R;

int main() {
    memset(dp, -1, sizeof(dp));
    init();
    cin >> L >> R;
    //printf("%d %d\n", countCute(L), countCute(R));
    int ans = sub(countCute(R), countCute(L));
    if (isCute(L)) ans = add(ans, 1);
    printf("%d", ans);
    return 0;
}
