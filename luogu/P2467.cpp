// https://www.luogu.org/problemnew/show/P2467
// [SDOI2010]地精部落

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 4210;
int N, P;
int64_t dp[MAXN][4];
int binom[MAXN][MAXN];

void generate() {
    binom[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        binom[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            binom[i][j] = (binom[i-1][j] + binom[i-1][j-1]) % P;
        }
    }
}

int main() {
    scanf("%d%d", &N, &P);
    generate();
    dp[1][1] = 1;
    for (int i = 2; i <= N; i++) {
        dp[i][0] = dp[i-1][1];
        dp[i][2] = dp[i-1][0] + dp[i-1][3];
        dp[i][3] = dp[i-1][1];
        for (int j = 1; j <= i-2; j++) {
            int c1 = (binom[i-1][j] * dp[j][1]) % P;
            int c3 = (binom[i-1][j] * dp[j][3]) % P;
            dp[i][0] += (c1 * dp[i-1-j][0]) % P;
            dp[i][1] += (c1 * dp[i-1-j][1]) % P;
            dp[i][2] += (c3 * dp[i-1-j][0]) % P;
            dp[i][3] += (c3 * dp[i-1-j][1]) % P;
        }
        dp[i][0] %= P;
        dp[i][1] %= P;
        dp[i][2] %= P;
        dp[i][3] %= P;
    }
    int ans = (dp[N][0] + dp[N][1] + dp[N][2] + dp[N][3]) % P;
    printf("%d\n", ans);
    return 0;
}
