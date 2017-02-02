// https://www.luogu.org/problem/show?pid=1373
// 小a和uim之大逃离

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 810;
int A[MAXN][MAXN];
int dp[MAXN][MAXN][16];
int N, M, K;
const int MOD = 1000000007;

int add(int a, int b) {
    return (a + b) % MOD;
}

int sub(int a, int b) {
    return (a - b + MOD) % MOD;
}

bool inRange(int i, int j) {
    return (0 <= i && i < N && 0 <= j && j < M);
}

int main() {
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    for (int i = N-1; i >= 0; i--) {
        for (int j = M-1; j >= 0; j--) {
            for (int k = 0; k <= K; k++) {
                int right = -1, down = -1;
                if (j + 1 < M) {
                    right = (k - A[i][j] + A[i][j+1] + K + 1) % (K + 1);
                }
                if (i + 1 < N) {
                    down  = (k - A[i][j] + A[i+1][j] + K + 1) % (K + 1);
                }

                if (j + 1 < M && right == 0) {
                    dp[i][j][k] = add(dp[i][j][k], 1);
                }
                if (i + 1 < N && down == 0) {
                    dp[i][j][k] = add(dp[i][j][k], 1);
                }

                if (inRange(i+1, j+1)) {
                    dp[i][j][k] = add(dp[i][j][k], dp[i+1][j+1][right]);
                    dp[i][j][k] = add(dp[i][j][k], dp[i+1][j+1][down]);
                }
                if (inRange(i+2, j)) {
                    dp[i][j][k] = add(dp[i][j][k], dp[i+2][j][down]);
                }
                if (inRange(i, j+2)) {
                    dp[i][j][k] = add(dp[i][j][k], dp[i][j+2][right]);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ans = add(ans, dp[i][j][0]);
        }
    }

    printf("%d\n", ans);
    return 0;
}
