// https://www.luogu.org/problemnew/show/P2217
// [HAOI2007]分割矩阵

#include <bits/stdc++.h>
using namespace std;

int ROW, COL, N;
int M[11][11], P[11][11];
int dp[11][11][11][11][11];

int main() {
    scanf("%d%d%d", &ROW, &COL, &N);
    memset(dp, 0x3F, sizeof(dp));
    for (int i = 1; i <= ROW; i++) {
        for (int j = 1; j <= COL; j++) {
            scanf("%d", &M[i][j]);
            P[i][j] = P[i-1][j] + P[i][j-1] - P[i-1][j-1] + M[i][j];
        }
    }
    for (int i = 1; i <= ROW; i++) {
        for (int j = 1; j <= COL; j++) {
            for (int i2 = i; i2 <= ROW; i2++) {
                for (int j2 = j; j2 <= COL; j2++) {
                    int a = P[i2][j2] - P[i2][j-1] - P[i-1][j2] +
                        P[i-1][j-1];
                    dp[i][j][i2][j2][1] = a*a;
                }
            }
        }
    }
    for (int n = 2; n <= N; n++) {
        for (int sx = 1; sx <= ROW; sx++) {
            for (int sy = 1; sy <= COL; sy++) {
                for (int i = 1; i <= ROW+1-sx; i++) {
                    int i2 = i + sx - 1;
                    for (int j = 1; j <= COL+1-sy; j++) {
                        int j2 = j + sy - 1;
                        int &res = dp[i][j][i2][j2][n];
                        for (int k = i+1; k <= i2; k++) {
                            for (int n1 = 1; n1 < n; n1++) {
                                res = min(res,
                                          dp[i][j][k-1][j2][n1] +
                                          dp[k][j][i2][j2][n-n1]);
                            }
                        }
                        for (int k = j+1; k <= j2; k++) {
                            for (int n1 = 1; n1 < n; n1++) {
                                res = min(res,
                                          dp[i][j][i2][k-1][n1] +
                                          dp[i][k][i2][j2][n-n1]);
                            }
                        }
                    }
                }
            }
        }
    }

    double ret = sqrt(1.0/N * (dp[1][1][ROW][COL][N] -
                               1.0*P[ROW][COL]*P[ROW][COL]/N));
    printf("%.2f", ret);

    return 0;
}
