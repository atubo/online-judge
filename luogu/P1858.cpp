// https://www.luogu.org/problemnew/show/P1858
// 多人背包

#include <bits/stdc++.h>
using namespace std;

int dp[5010][51];

int K, C, N;
int W[210], V[210];
int tmp[51];

void merge(int *fi, int *fj, int v) {
    int p = 0, q = 0;
    int idx = 0;
    while (idx < K && (p < K && fi[p] >= 0) && (q < K && fj[q] >= 0)) {
        if (fi[p] >= v + fj[q]) {
            tmp[idx++] = fi[p++];
        } else {
            tmp[idx++] = v + fj[q++];
        }
    }
    if (idx < K) {
        while (idx < K && p < K && fi[p] >= 0) {
            tmp[idx++] = fi[p++];
        }
        while (idx < K && q < K && fj[q] >= 0) {
            tmp[idx++] = v + fj[q++];
        }
    }
    for (int i = 0; i < idx; i++) {
        fi[i] = tmp[i];
    }
}

int main() {
    scanf("%d%d%d", &K, &C, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &W[i], &V[i]);
    }
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = C; j >= W[i]; j--) {
            merge(dp[j], dp[j-W[i]], V[i]);
        }
    }
    int ans = 0;
    for (int i = 0; i < K; i++) {
        if (dp[C][i] > 0) ans += dp[C][i];
    }
    printf("%d", ans);
    return 0;
}
