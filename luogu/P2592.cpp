// https://www.luogu.org/problemnew/show/P2592
// [ZJOI2008]生日聚会

#include <bits/stdc++.h>
using namespace std;

int dp[302][152][22][22];

int main() {
    int N, M, K, MOD = 12345678;
    scanf("%d%d%d", &N, &M, &K);
    dp[0][0][0][0] = 1;
    for (int i = 0; i <= N+M; i++) {
        for (int j = 0; j <= min(i, N); j++) {
            for (int a = 0; a <= K; a++) {
                for (int b = 0; b <= K; b++) {
                    (dp[i+1][j+1][a+1][max(0, b-1)] += dp[i][j][a][b]) %= MOD;
                    (dp[i+1][j][max(0, a-1)][b+1] += dp[i][j][a][b]) %= MOD;
                }
            }
        }
    }

    int ans = 0;
    for (int a = 0; a <= K; a++) {
        for (int b = 0; b <= K; b++) {
            (ans += dp[N+M][N][a][b]) %= MOD;
        }
    }
    printf("%d\n", ans);
    return 0;
}
