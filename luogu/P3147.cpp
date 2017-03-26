// https://www.luogu.org/problem/show?pid=3147
// [USACO16OPEN]262144

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 262154, MAXM = 62;
int dp[MAXM][MAXN];
int N;

int main() {
    scanf("%d", &N);
    memset(dp, -1, sizeof(dp));
    int ret = 0;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        dp[x][i] = i;
        ret = max(ret, x);
    }

    for (int p = 2; p <= 60; p++) {
        for (int i = 0; i < N; i++) {
            if (dp[p-1][i] >= 0 && dp[p-1][i] < N-1 &&
                dp[p-1][dp[p-1][i]+1] >= 0) {
                dp[p][i] = dp[p-1][dp[p-1][i]+1];
                ret = max(p, ret);
            }
        }
    }

    printf("%d\n", ret);
    return 0;
}
