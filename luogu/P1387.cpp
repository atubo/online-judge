// https://www.luogu.org/problem/show?pid=1387
// 最大正方形

#include <bits/stdc++.h>
using namespace std;

int dp[110][110];
int N, M;

int main() {
    scanf("%d %d", &N, &M);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0;  j < M; j++) {
            scanf("%d", &dp[i][j]);
            if (dp[i][j] && i > 0 && j > 0) {
                dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
            }
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
