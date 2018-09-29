// https://www.luogu.org/problemnew/show/P3830
// [SHOI2012]随机树

#include <bits/stdc++.h>
using namespace std;

void solve1(int n) {
    double d = 0;
    for (int i = 2; i <= n; i++) {
        d += 2.0 / i;
    }
    printf("%.6f\n", d);
}

double dp[110][110];

void solve2(int n) {
    for (int i = 1; i <= n; i++) dp[i][0] = 1.0;
    for (int i = 2; i <= n; i++) {
        for (int k = 1; k < i; k++) {
            for (int j = 1; j <= i-1; j++) {
                dp[i][k] += dp[j][k-1] + dp[i-j][k-1] -
                    dp[j][k-1]*dp[i-j][k-1];
            }
            dp[i][k] /= i-1;
        }
    }
    double ans = 0;
    for (int k = 1; k < n; k++) {
        ans += dp[n][k];
    }
    printf("%.6f\n", ans);
}

int main() {
    int q, n;
    scanf("%d%d", &q, &n);
    if (q == 1) solve1(n);
    else solve2(n);
    return 0;
}
