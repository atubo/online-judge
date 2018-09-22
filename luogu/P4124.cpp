// https://www.luogu.org/problemnew/show/P4124
// [CQOI2016]手机号码

#include <bits/stdc++.h>
using namespace std;

const int LEN = 11;

int64_t pow(int64_t x, int n) {
    int64_t ret = 1;
    for (int i = 1; i <= n; i++) {
        ret *= x;
    }
    return ret;
}

void setMask(int p, int &mask) {
    if (p == 4) mask |= 1;
    if (p == 8) mask |= 2;
}

int64_t dp1[10][10][12];
int64_t dp2[12][4];
int64_t dp3[10][10][12][4];

void init() {
    memset(dp1, -1, sizeof(dp1));
    memset(dp2, -1, sizeof(dp2));
    memset(dp3, -1, sizeof(dp3));
}

int64_t solve1(const string &s, int p1, int p2, int d, bool clamp) {
    if (d == LEN) return 1;
    if (!clamp && dp1[p1][p2][d] != -1) return dp1[p1][p2][d];
    int64_t ret = 0;
    if (clamp) {
        for (int x = 0; x <= s[d] - '0'; x++) {
            if (p1 == p2 && p2 == x) continue;
            ret += solve1(s, p2, x, d+1, x == s[d]-'0');
        }
    } else {
        for (int x = 0; x < 10; x++) {
            if (p1 == p2 && p2 == x) continue;
            ret += solve1(s, p2, x, d+1, false);
        }
        dp1[p1][p2][d] = ret;
    }
    return ret;
}

int64_t solve1(const string &s) {
    int64_t ans = 0;
    int d2 = stoi(s.substr(0, 2));
    for (int x = 10; x <= d2; x++) {
        int p1 = x / 10;
        int p2 = x % 10;
        ans += solve1(s, p1, p2, 2, x == d2);
    }
    return ans;
}

int64_t solve2(const string &s, int d, int mask, bool clamp) {
    if (d == LEN) return (mask == 3);
    if(!clamp && dp2[d][mask] != -1) return dp2[d][mask];
    int64_t ret = 0;
    if (clamp) {
        for (int x = (d==0); x <= s[d] - '0'; x++) {
            int nm = mask;
            setMask(x, nm);
            ret += solve2(s, d+1, nm, x == s[d]-'0');
        }
    } else {
        for (int x = (d==0); x < 10; x++) {
            int nm = mask;
            setMask(x, nm);
            ret += solve2(s, d+1, nm, false);
        }
        dp2[d][mask] = ret;
    }
    return ret;
}

int64_t solve2(const string &s) {
    int64_t ans = solve2(s, 0, 0, true);
    return ans;
}

int64_t solve3(const string &s, int p1, int p2, int d, int mask,
               bool clamp) {
    if (d == LEN) return mask == 3;
    if (!clamp && dp3[p1][p2][d][mask] != -1) return dp3[p1][p2][d][mask];
    int64_t ret = 0;
    if (clamp) {
        for (int x = 0; x <= s[d] - '0'; x++) {
            if (p1 == p2 && p2 == x) continue;
            int nm = mask;
            setMask(x, nm);
            ret += solve3(s, p2, x, d+1, nm, x == s[d]-'0');
        }
    } else {
        for (int x = 0; x < 10; x++) {
            if (p1 == p2 && p2 == x) continue;
            int nm = mask;
            setMask(x, nm);
            ret += solve3(s, p2, x, d+1, nm, false);
        }
        dp3[p1][p2][d][mask] = ret;
    }
    return ret;
}

int64_t solve3(const string &s) {
    int64_t ans = 0;
    int d2 = stoi(s.substr(0, 2));
    for (int x = 10; x <= d2; x++) {
        int p1 = x / 10;
        int p2 = x % 10;
        int mask = 0;
        setMask(p1, mask);
        setMask(p2, mask);
        ans += solve3(s, p1, p2, 2, mask, x == d2);
    }
    return ans;
}

int64_t solve(const string &s) {
    init();
    int64_t ans = stol(s) - pow(10, LEN-1) + 1;
    ans = ans - solve1(s) - solve2(s) + solve3(s);
    return ans;
}

bool check(const string &s) {
    bool ok = false;
    for (int i = 2; i < LEN; i++) {
        if (s[i] == s[i-1] && s[i] == s[i-2]) {
            ok = true;
            break;
        }
    }
    if (!ok) return false;
    int mask = 0;
    for (int i = 0; i < LEN; i++) {
        int x = s[i] - '0';
        setMask(x, mask);
    }
    return mask != 3;
}

int main() {
    string L, R;
    cin >> L >> R;
    int64_t ans = solve(R) - solve(L) + check(L);
    cout << ans;
    return 0;
}
