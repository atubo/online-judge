// https://www.luogu.org/problemnew/show/P1130
// 红牌

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2048;
int N, M;
int A[MAXN][MAXN], dp[MAXN][MAXN];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 0; i < M; i++) dp[0][i] = A[i][0];
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dp[i][j] = A[j][i] + min(dp[i-1][j], dp[i-1][(j+M-1)%M]);
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < M; i++) {
        ans = min(ans, dp[N-1][i]);
    }
    printf("%d\n", ans);
    return 0;
}
