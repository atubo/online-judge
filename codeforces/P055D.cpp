// http://codeforces.com/problemset/problem/55/D
// Beautiful numbers

#include <bits/stdc++.h>
using namespace std;

const int MOD = 2520;
int64_t dp[MOD][48][19][10];
int idx[MOD+10];

void init() {
    int num = 0;
    for (int i = 1; i <= MOD; i++) {
        if (MOD % i == 0) idx[i] = num++;
    }

    memset(dp, -1, sizeof(dp));
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a%b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int64_t dfs(int prer, int prelcm, int pos, int d, const vector<int>& digits,
            bool bounded) {
    if (!bounded && dp[prer][idx[prelcm]][pos][d] != -1) {
        return dp[prer][idx[prelcm]][pos][d];
    }
    int currlcm = (d == 0 ? prelcm : lcm(prelcm, d));
    int currr = (prer * 10 + d) % MOD;
    int64_t ret = 0;
    if (pos == 0) {
        ret = ((currr % currlcm) == 0);
    } else {
        int maxd = (bounded && d == digits[pos]) ? digits[pos-1]: 9;
        for (int nextd = 0; nextd <= maxd; nextd++) {
            ret += dfs(currr, currlcm, pos-1, nextd, digits, bounded && d==digits[pos]);
        }
    }
    if (!(bounded && d == digits[pos])) {
        dp[prer][idx[prelcm]][pos][d] = ret;
    }
    return ret;
}

int64_t solve(int64_t a) {
    if (a == 0) return 1;
    vector<int> digits;
    while (a > 0) {
        digits.push_back(a % 10);
        a = a/10;
    }
    int64_t ans = 0;
    int N = digits.size();
    for (int d = 0; d <= digits[N-1]; d++) {
        ans += dfs(0, 1, N-1, d, digits, true);
    }
    return ans;
}

int64_t solve(int64_t a, int64_t b) {
    return solve(b) - solve(a-1);
}

int main() {
    init();
    int T;
    cin >> T;
    while (T--) {
        int64_t a, b;
        cin >> a >> b;
        cout << solve(a, b) << endl;
    }

    return 0;
}
