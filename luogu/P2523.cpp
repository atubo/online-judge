// https://www.luogu.org/problemnew/show/P2523
// [HAOI2011]Problem c

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310;
int N, M;
int MOD;

int binom[MAXN][MAXN];

void init() {
    binom[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; j++) {
            binom[i][j] = (binom[i-1][j-1] + binom[i-1][j]) % MOD;
        }
    }
}

int T;
bool A[MAXN];
int tot[MAXN];
int dp[MAXN][MAXN];

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int solve() {
    scanf("%d%d%d", &N, &M, &MOD);
    init();
    memset(A, 0, sizeof(A));
    memset(dp, 0, sizeof(dp));
    memset(tot, 0, sizeof(tot));
    bool ok = true;
    for (int i = 0; i < M; i++) {
        int p, q;
        scanf("%d%d", &p, &q);
        while (q <= N && A[q]) q++;
        if (q > N) ok = false;
        A[q] = true;
    }
    if (!ok) return -1;
    for (int i = N; i >= 1; i--) {
        tot[i] = A[i] + tot[i+1];
    }

    dp[N+1][0] = 1;
    for (int i = N; i >= 1; i--) {
        for (int j = 0; j <= N-i+1-tot[i]; j++) {
            for (int k = 0; k <= j; k++) {
                dp[i][j] = add(dp[i][j],
                               mul(dp[i+1][j-k], binom[j][k]));
            }
        }
    }
    return dp[1][N-M];
}

int main() {
    scanf("%d", &T);
    while (T--) {
        int ret = solve();
        if (ret >= 0) {
            printf("YES %d\n", ret);
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
