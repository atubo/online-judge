// https://www.luogu.org/problem/show?pid=1896
// [SCOI2005]互不侵犯King

#include <bits/stdc++.h>
using namespace std;

int N, K;
int64_t dp[2][1024][90];

int getnext(int k) {
    if (k & (1 << N)) k -= (1 << N);
    return k << 1;
}

bool check(int i, int j, int k) {
    if (i && j && (k & (1 << N))) return false;
    if (i && (k & (1 << (N-1)))) return false;
    if (i && (j < N-1) && (k & (1 << (N-2)))) return false;
    if (j && (k & 1)) return false;
    return true;
}

int main() {
    scanf("%d%d", &N, &K);
    dp[0][0][0] = 1;
    int cur = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cur ^= 1;
            memset(dp[cur], 0, sizeof(dp[cur]));
            for (int k = 0; k < (1 << (N+1)); k++) {
                int now = getnext(k);
                for (int t = 0; t <= K; t++) {
                    dp[cur][now][t] += dp[cur^1][k][t];
                    if (t < K && check(i, j, k)) dp[cur][now+1][t+1] += dp[cur^1][k][t];
                }
            }
        }
    }
    int64_t ans = 0;
    for (int k = 0; k < (1 << (N+1)); k++) {
        ans += dp[cur][k][K];
    }
    printf("%lld\n", ans);
    return 0;
}
