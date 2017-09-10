// https://www.luogu.org/problem/show?pid=2736
// “破锣摇滚”乐队 Raucous Rockers

#include <bits/stdc++.h>
using namespace std;

int N, T, M;

int dp[2][20][21];

int main() {
    int curr = 0;
    memset(dp[curr], -1, sizeof(dp[curr]));
    dp[curr][0][0] = 0;
    scanf("%d%d%d", &N, &T, &M);
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        int prev = curr;
        curr = prev ^ 1;
        memset(dp[curr], -1, sizeof(dp[curr]));
        for (int m = 0; m < M; m++) {
            for (int t = 0; t <= T; t++) {
                int d = dp[prev][m][t];
                if (d >= 0) {
                    dp[curr][m][t] = max(dp[curr][m][t], d);
                    if (t + x <= T) {
                        dp[curr][m][t+x] = max(dp[curr][m][t+x], d+1);
                    } else if (m < M-1 && x <= T) {
                        dp[curr][m+1][x] = max(dp[curr][m+1][x], d+1);
                    }
                }
            }
        }
    }

    int ret = 0;
    for (int m = 0; m < M; m++) {
        for (int t = 0; t <= T; t++) {
            ret = max(ret, dp[curr][m][t]);
        }
    }
    printf("%d\n", ret);
    return 0;
}
