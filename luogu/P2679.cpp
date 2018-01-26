// https://www.luogu.org/problemnew/show/P2679
// 子串

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int N, M, K;
int dp1[1010][210][210], dp2[2][1010][210];
char S[1010], T[210];

int main() {
    scanf("%d%d%d", &N, &M, &K);
    scanf("%s", S);
    scanf("%s", T);
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            dp2[0][i][j] = (j == 0);
        }
    }

    for (int k = 1; k <= K; k++) {
        int curr = k & 1, prev = curr ^ 1;
        memset(dp2[curr], 0, sizeof(dp2[curr]));
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                if (S[i-1] == T[j-1]) {
                    dp1[i][j][k] = dp1[i-1][j-1][k] + dp2[prev][i-1][j-1];
                    dp1[i][j][k] %= MOD;
                } else {
                    dp1[i][j][k] = 0;
                }
                dp2[curr][i][j] = (dp2[curr][i-1][j] + dp1[i][j][k]) % MOD;
            }
        }
    }

    printf("%d\n", dp2[K&1][N][M]);
    return 0;
}
