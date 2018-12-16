// https://www.luogu.org/problemnew/show/P4026
// [SHOI2008]循环的债务

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int X1, X2, X3;

int FV[7] = {-1, 100, 50, 20, 10, 5, 1};
int CNT[3][7];
int S[3], T[3];
int dp[7][1001][1001];

int main() {
    scanf("%d%d%d", &X1, &X2, &X3);
    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= 6; j++) {
            scanf("%d", &CNT[i][j]);
            S[i] += FV[j] * CNT[i][j];
        }
    }

    int tot = 0;
    for (int i = 0; i < 3; i++) {
        tot += S[i];
    }
    T[0] = S[0] - X1 + X3;
    T[1] = S[1] - X2 + X1;
    T[2] = S[2] - X3 + X2;

    if (T[0] < 0 || T[1] < 0 || T[2] < 0) {
        printf("impossible\n");
        return 0;
    }

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j <= 1000; j++) {
            for (int k = 0; k <= 1000; k++) {
                dp[i][j][k] = INF;
            }
        }
    }

    dp[0][S[0]][S[1]] = 0;
    for (int i = 0; i < 6; i++) {
        for (int s1 = 0; s1 <= tot; s1++) {
            int remain = tot - s1;
            for (int s2 = 0; s2 <= remain; s2++) {
                if (dp[i][s1][s2] == INF) continue;
                int tc = CNT[0][i+1] + CNT[1][i+1] + CNT[2][i+1];
                for (int c1 = 0; c1 <= tc; c1++) {
                    int rc = tc - c1;
                    for (int c2 = 0; c2 <= rc; c2++) {
                        int d1 = c1 - CNT[0][i+1];
                        int d2 = c2 - CNT[1][i+1];
                        int sa = s1 + FV[i+1]*d1;
                        int sb = s2 + FV[i+1]*d2;
                        dp[i+1][sa][sb] = min(dp[i+1][sa][sb],
                                              dp[i][s1][s2] +
                                              (abs(d1) +
                                               abs(d2) +
                                               abs(d1+d2))/2);
                    }
                }
            }
        }
    }

    int ret = dp[6][T[0]][T[1]];
    if (ret == INF) printf("impossible\n");
    else printf("%d\n", ret);

    return 0;
}
