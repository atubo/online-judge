// https://www.luogu.org/problem/show?pid=1437
// [HNOI2004]敲砖块

#include <bits/stdc++.h>
using namespace std;

int N, M;
int A[55][55];
int dp[55][55][1300];

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = N; j >= i; j--) {
            scanf("%d", &A[j][i]);
        }
    }

    for (int i = 1; i <= N; i++) {
        int ps = 0;
        for (int j = 0; j <= i; j++) {
            ps += A[i][j];
            for (int k = j*(j+1)/2; k <= i*(i-1)/2+j; k++) {
                for (int p = j-1; p <= i-1; p++) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][p][k-j] + ps);
                }
            }
        }
    }

    int ret = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            ret = max(ret, dp[i][j][M]);
        }
    }

    printf("%d\n", ret);

    return 0;
}
