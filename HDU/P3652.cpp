// http://acm.hdu.edu.cn/showproblem.php?pid=3652
// B-number

#include <bits/stdc++.h>
using namespace std;

int dp[2][13][10][10][10];
int digits[11];

int dfs(bool seen, int dprev, int r, int pos, int d, bool bounded) {
    int& dpEntry = dp[seen][r][pos][dprev][d];
    bounded = bounded && d == digits[pos];
    if (!bounded && dp[seen][r][pos][dprev][d] != -1) {
        return dp[seen][r][pos][dprev][d];
    }

    seen = seen || (dprev == 1 && d == 3);
    r = (10 * r + d) % 13;
    if (pos == 0) {
        return seen && (r == 0);
    }

    int maxd = (bounded ? digits[pos-1]: 9);
    int ret = 0;
    for (int nextd = 0; nextd <= maxd; nextd++) {
        ret += dfs(seen, d, r, pos-1, nextd, bounded);
    }

    if (!bounded) dpEntry = ret;
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    int a;
    while (scanf("%d", &a) == 1) {
        int n = 0;
        while (a > 0) {
            digits[n++] = a % 10;
            a = a / 10;
        }
        int ans = 0;
        for (int d = 0; d <= digits[n-1]; d++) {
            ans += dfs(false, 0, 0, n-1, d, true);
        }
        printf("%d\n", ans);
    }
    return 0;
}

