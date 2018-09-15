// https://www.luogu.org/problemnew/show/P3226
// [HNOI2012]集合选数

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000001;
const int R = 17;
int C;
int N;
int dp[18][1<<13];
int64_t p2[18], p3[14];
int tot;

void init() {
    p2[0] = p3[0] = 1;
    for (int i = 1; i <= 17; i++) p2[i] = p2[i-1] * 2;
    for (int i = 1; i <= 13; i++) p3[i] = p3[i-1] * 3;
}

int64_t calc(int s, int i, int j) {
    return 1LL * s * p2[i] * p3[j];
}

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int solve(int s) {
    C = 1;
    int64_t tmp = s * 3;
    while (tmp <= N) {
        tmp *= 3;
        C++;
    }
    C++;
    memset(dp[0], 0, (1<<C)*sizeof(int));
    dp[0][0] = tot = 1;
    for (int i = 1; i < (1<<C); i++) {
        int x = __builtin_clz(i);
        if (calc(s, 0, 31-x) > N) break;
        if (i & (i << 1)) continue;
        dp[0][i] = 1;
        tot = add(tot, dp[0][i]);
    }

    for (int i = 1; i < R; i++) {
        memset(dp[i], 0, (1<<C)*sizeof(int));
        dp[i][0] = tot;
        for (int j = 1; j < (1<<C); j++) {
            int x = __builtin_clz(j);
            if (calc(s, i, 31-x) > N) break;
            if (j & (j << 1)) continue;

            x = ((1<<C) - 1) & (~j);
            for (int k = x; k; ) {
                k = (k-1) & x;
                dp[i][j] = add(dp[i][j], dp[i-1][k]);
            }
            tot = add(tot, dp[i][j]);
        }
    }
    int ans = 0;
    for (int i = 0; i < (1<<C); i++) {
        ans = add(ans, dp[R-1][i]);
    }
    return ans;
}

int main() {
    init();
    scanf("%d", &N);
    int ans = 1;
    for (int i = 1; i <= N; i++) {
        if ((i%2) != 0 && (i%3) != 0) {
            ans = mul(ans, solve(i));
        }
    }
    printf("%d\n", ans);
    return 0;
}
