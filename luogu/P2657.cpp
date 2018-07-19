// https://www.luogu.org/problemnew/show/P2657
// [SCOI2009]windy数

#include <bits/stdc++.h>
using namespace std;

int dp[12][10];
int digits[12];
int A, B;

int dfs(int pos, int d, bool bounded, bool leading_zero) {
    int& res = dp[pos][d];
    bounded = bounded && d == digits[pos];
    if (!bounded && !leading_zero && res != -1) {
        return res;
    }
    leading_zero = (leading_zero && d == 0);

    if (pos == 0) {
        return res = 1;
    }

    int maxd = (bounded ? digits[pos-1]: 9);
    int ans = 0;
    for (int nextd = 0; nextd <= maxd; nextd++) {
        if (!leading_zero && abs(nextd - d) < 2) continue;
        ans += dfs(pos-1, nextd, bounded, leading_zero);
    }
    if (!bounded && !leading_zero) res = ans;
    return ans;
}

int solve(int x) {
    memset(dp, -1, sizeof(dp));
    memset(digits, 0, sizeof(digits));
    string s = to_string(x);
    int len = s.length();
    for (int i = 0; i < len; i++) {
        digits[i] = s[len-1-i] - '0';
    }

    int ans = 0;
    for (int i = 0; i <= digits[len-1]; i++) {
        ans += dfs(len-1, i, i==digits[len-1], true);
    }
    return ans;
}


int main() {
    scanf("%d%d", &A, &B);
    int ans = solve(B) - solve(A-1);
    printf("%d\n", ans);
    return 0;
}
