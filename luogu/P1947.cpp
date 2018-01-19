// https://www.luogu.org/problemnew/show/P1947
// 笨笨当粉刷匠_NOI导刊2011提高（10）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 52;
int N, M, T;
int wall[MAXN][MAXN], ps[MAXN][MAXN];
int dp[MAXN][MAXN][2];
int C[MAXN][MAXN];
int dp2[MAXN][MAXN*MAXN];

int main() {
    scanf("%d%d%d", &N, &M, &T);
    for (int i = 0; i < N; i++) {
        char line[MAXN];
        scanf("%s", line);
        for (int j = 1; j <= M; j++) {
            wall[i][j] = line[j-1] - '0';
            ps[i][j] = ps[i][j-1] + wall[i][j];
        }
    }

    for (int row = 0; row < N; row++) {
        memset(dp, 0, sizeof(dp));
        C[row][0] = 0;
        for (int t = 1; t <= M; t++) {
            for (int i = t; i <= M; i++) {
                for (int j = t-1; j < i; j++) {
                    int ones = ps[row][i] - ps[row][j];
                    int zeros = i - j - ones;
                    dp[i][t][0] = max(dp[i][t][0],
                                      dp[j][t-1][1] + zeros);
                    dp[i][t][1] = max(dp[i][t][1],
                                      dp[j][t-1][0] + ones);
                }
            }
            C[row][t] = max(C[row][t-1], max(dp[M][t][0], dp[M][t][1]));
        }
    }

#if 0
    for (int i = 0; i < N; i++) {
        for (int t = 0; t <= M; t++) {
            printf("%d ", C[i][t]);
        }
        printf("\n");
    }
#endif

    for (int i = 0; i <= M; i++) {
        dp2[0][i] = C[0][i];
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j <= (i+1)*M; j++) {
            for (int k = 0; k <= M; k++) {
                dp2[i+1][j+k] = max(dp2[i+1][j+k],
                                    dp2[i][j] + C[i+1][k]);
            }
        }
    }
    printf("%d\n", dp2[M][T]);

    return 0;
}
