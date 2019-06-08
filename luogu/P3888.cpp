// https://www.luogu.org/problemnew/show/P3888
// [GDOI2014]拯救莫莉斯

#include <bits/stdc++.h>
using namespace std;

int N, M;
int A[52][52];
int C[52][1<<8];
int dp[52][1<<8][1<<8];
int dp2[52][1<<8][1<<8];
int ALL;

int main() {
    scanf("%d%d", &N, &M);
    ALL = (1<<M) - 1;
    memset(dp, 0x3F, sizeof(dp));
    memset(dp2, 0x3F, sizeof(dp2));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    if (N == 1) {
        printf("1 %d\n", A[0][0]);
        return 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < (1<<M); j++) {
            int m = j;
            while (m > 0) {
                int d = __builtin_ctz(m);
                C[i][j] += A[i][d];
                m -= (1<<d);
            }
        }
    }

    for (int i = 0; i < (1<<M); i++) {
        for (int j = 0; j < (1<<M); j++) {
            int m = (i) | (i<<1) | (i>>1) | j;
            if ((m&ALL) != ALL) continue;
            dp[1][i][j] = C[0][i] + C[1][j];
            dp2[1][i][j] = __builtin_popcount(i) + __builtin_popcount(j);
        }
    }

    for (int i = 2; i < N; i++) {
        for (int m1 = 0; m1 <= ALL; m1++) {
            for (int m2 = 0; m2 <= ALL; m2++) {
                for (int m3 = 0; m3 <= ALL; m3++) {
                    int m = m2 | (m2<<1) | (m2>>1) | m1 | m3;
                    if ((m&ALL) != ALL) continue;
                    int c = dp[i-1][m1][m2] + C[i][m3];
                    int k = dp2[i-1][m1][m2] + __builtin_popcount(m3);
                    if ((c < dp[i][m2][m3]) ||
                        (c == dp[i][m2][m3] && k < dp2[i][m2][m3])) {
                        dp[i][m2][m3] = c;
                        dp2[i][m2][m3] = k;
                    }
                }
            }
        }
    }

    int ans = INT_MAX;
    int ans2 = INT_MAX;
    for (int i = 0; i <= ALL; i++) {
        for (int j = 0; j <= ALL; j++) {
            int m = j | (j<<1) | (j>>1) | i;
            if ((m&ALL) != ALL) continue;
            if ((dp[N-1][i][j] < ans) ||
                (dp[N-1][i][j] == ans && dp2[N-1][i][j] < ans2)) {
                ans = dp[N-1][i][j];
                ans2 = dp2[N-1][i][j];
            }
        }
    }
    printf("%d %d\n", ans2, ans);

    return 0;
}
