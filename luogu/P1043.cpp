// https://www.luogu.org/problem/show?pid=1043
// 数字游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int N, M;
int A[MAXN], ps[MAXN];
int dp[MAXN][MAXN][10];

int mod(int x) {
    return (x >= 0 ? x % 10 : 10 + (x % 10));
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        A[i+N] = A[i];
    }
    for (int i = 1; i <= 2*N; i++) {
        ps[i] = ps[i-1] + A[i];
    }

    for (int i = 1; i <= 2*N; i++) {
        for (int j = i+1; j <= 2*N; j++) {
            dp[i][j][1] = mod(ps[j-1] - ps[i-1]);
        }
    }
    for (int m = 2; m <= M; m++) {
        for (int i = 1; i <= 2*N; i++) {
            for (int j = i+1; j <= 2*N; j++) {
                dp[i][j][m] = -1;
                for (int k = i+1; k < j; k++) {
                    dp[i][j][m] = max(dp[i][j][m], dp[i][k][1] * dp[k][j][m-1]);
                }
            }
        }
    }

    int resmax = -1;
    for (int i = 1; i <= N; i++) {
        resmax = max(resmax, dp[i][i+N][M]);
    }

    for (int m = 2; m <= M; m++) {
        for (int i = 1; i <= 2*N; i++) {
            for (int j = i+1; j <= 2*N; j++) {
                dp[i][j][m] = INT_MAX;
                for (int k = i+1; k < j; k++) {
                    if (dp[k][j][m-1] < INT_MAX) {
                        dp[i][j][m] = min(dp[i][j][m], dp[i][k][1] * dp[k][j][m-1]);
                    }
                }
            }
        }
    }

    int resmin = INT_MAX;
    for (int i = 1; i <= N; i++) {
        resmin = min(resmin, dp[i][i+N][M]);
    }
    printf("%d\n%d\n", resmin, resmax);

    return 0;
}
