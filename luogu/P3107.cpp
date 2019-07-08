// https://www.luogu.org/problemnew/show/P3107
// [USACO14OPEN]里程表Odometer

#include <bits/stdc++.h>
using namespace std;

int64_t dp[20][20];
int64_t dp2[20][10][10];

int64_t solve(const vector<int> &s, int p, int x, int k, bool clamped) {
    const int n = s.size();
    if (p == n) return k == 0;
    if (!clamped && dp[p][k] != -1) return dp[p][k];
    int64_t ret = 0;
    int start = (clamped ? s[p] : 0);
    for (int d = start; d <= 9; d++) {
        bool c = (clamped && (d == s[p]));
        if (d == x) {
            if (k > 0) {
                ret += solve(s, p+1, x, k-1, c);
            }
        } else {
            ret += solve(s, p+1, x, k, c);
        }
    }
    if (!clamped) dp[p][k] = ret;
    return ret;
}

int64_t solve(const vector<int> &s, int x, int k) {
    memset(dp, -1, sizeof(dp));
    int64_t ret = 0;
    for (int d = s[0]; d <= 9; d++) {
        bool c = (d == s[0]);
        ret += solve(s, 1, x, k-(d==x), c);
    }
    return ret;
}

int64_t solve2(const vector<int> &s,
               int p, int x1, int x2, int k1, int k2, bool clamped) {
    if (p == (int)s.size()) return 1;
    if (!clamped && dp2[p][k1][k2] != -1) return dp2[p][k1][k2];
    int64_t ret = 0;
    if (clamped) {
        if (x1 > s[p] && k1 > 0) {
            ret += solve2(s, p+1, x1, x2, k1-1, k2, false);
        } else if (x1 == s[p] && k1 > 0) {
            ret += solve2(s, p+1, x1, x2, k1-1, k2, true);
        }
        if (x2 > s[p] && k2 > 0) {
            ret += solve2(s, p+1, x1, x2, k1, k2-1, false);
        } else if (x2 == s[p] && k2 > 0) {
            ret += solve2(s, p+1, x1, x2, k1, k2-1, true);
        }
    } else {
        if (k1 > 0) ret += solve2(s, p+1, x1, x2, k1-1, k2, false);
        if (k2 > 0) ret += solve2(s, p+1, x1, x2, k1, k2-1, false);
    }
    if (!clamped) dp2[p][k1][k2] = ret;
    return ret;
}

int64_t solve2(const vector<int> &s, int x1, int x2) {
    const int n = s.size();

    memset(dp2, -1, sizeof(dp2));
    int64_t ret = 0;
    if (x1 > s[0]) {
        ret += solve2(s, 1, x1, x2, n/2-1, n/2, false);
    } else if (x1 == s[0]) {
        ret += solve2(s, 1, x1, x2, n/2-1, n/2, true);
    }
    if (x2 > s[0]) {
        ret += solve2(s, 1, x1, x2, n/2, n/2-1, false);
    } else if (x2 == s[0]) {
        ret += solve2(s, 1, x1, x2, n/2, n/2-1, true);
    }
    return ret;
}

int64_t solve3(const vector<int> &s) {
    const int n = s.size();
    int64_t ret = 0;
    for (int k = n/2+1; k <= n; k++) {
        for (int d = 0; d <= 9; d++) {
            ret += solve(s, d, k);
        }
    }
    if ((n & 1) == 0) {
        for (int d = 0; d <= 9; d++) {
            ret += solve(s, d, n/2);
        }
        for (int d1 = 0; d1 <= 9; d1++) {
            for (int d2 = d1+1; d2 <= 9; d2++) {
                ret -= solve2(s, d1, d2);
            }
        }
    }
    return ret;
}

vector<int> convert(int64_t a) {
    vector<int> ret;
    while (a) {
        ret.push_back(a%10);
        a /= 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

bool check(int64_t a) {
    int cnt[10] = {0};
    int len = 0;
    while (a) {
        int d = a % 10;
        a /= 10;
        cnt[d]++;
        len++;
    }
    for (int d = 0; d <= 9; d++) {
        if (2*cnt[d] >= len) return true;
    }
    return false;
}

int main() {
    int64_t a, b;
    scanf("%ld%ld", &a, &b);
    auto s1 = convert(a);
    auto s2 = convert(b);
    int64_t ret = solve3(s1);
    for (int l = s1.size()+1; l <= (int)s2.size(); l++) {
        vector<int> s(l, 0);
        s[0] = 1;
        ret += solve3(s);
    }
    ret -= solve3(s2);
    ret += check(b);
    printf("%ld\n", ret);
    return 0;
}
