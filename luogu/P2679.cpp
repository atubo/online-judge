// https://www.luogu.org/problemnew/show/P2679
// 子串

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int N, M, K;
int dp1[1010][210], dp2[2][1010][210];
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
        memset(dp1, 0, sizeof(dp1));
        for (int j = 0; j <= M; j++) dp2[curr][0][j] = 0;
        for (int i = 0; i <= N; i++) dp2[curr][i][0] = 0;
        for (int i = k; i <= N; i++) {
            for (int j = k; j <= M; j++) {
                if (S[i-1] == T[j-1]) {
                    dp1[i][j] = dp1[i-1][j-1] + dp2[prev][i-1][j-1];
                    dp1[i][j] %= MOD;
                } else {
                    dp1[i][j] = 0;
                }
                dp2[curr][i][j] = (dp2[curr][i-1][j] + dp1[i][j]) % MOD;
            }
        }
    }

    printf("%d\n", dp2[K&1][N][M]);
    return 0;
}
