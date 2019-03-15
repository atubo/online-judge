// https://www.luogu.org/problemnew/show/P1171
// 售货员的难题

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
int N;
int D[MAXN][MAXN];
int dp[1<<19][MAXN];

int solve(int s, int j) {
    if (dp[s][j] >= 0) return dp[s][j];
    if (__builtin_popcount(s) == 1) return D[0][j];
    int &ret = dp[s][j] = INT_MAX;
    for (int k = 1; k < N; k++) {
        if (k == j) continue;
        if (((s>>(k-1)) & 1) == 0) continue;
        int s2 = s & (~(1<<(j-1)));
        ret = min(ret, solve(s2, k) + D[k][j]);
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &D[i][j]);
        }
    }
    const int ALL = (1<<(N-1)) - 1;
    for (int i = 1; i < N; i++) {
        solve(ALL, i);
    }
    int ans = INT_MAX;
    for (int i = 1; i < N; i++) {
        ans = min(ans, dp[ALL][i] + D[i][0]);
    }
    printf("%d\n", ans);
    return 0;
}
