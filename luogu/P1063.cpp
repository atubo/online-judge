// https://www.luogu.org/problem/show?pid=1063
// 能量项链

#include <bits/stdc++.h>
using namespace std;

int N;
int A[210], B[210];
int dp[210][210];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A[i+N] = A[i];
    }

    N *= 2;
    for (int i = 0; i < N; i++) {
        B[i] = A[(i+1)%N];
    }

    for (int len = 2; len <= N/2; len++) {
        for (int i = 0; i <= N - len; i++) {
            int j = i + len - 1;
            for (int k = i; k <= j - 1; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j] + A[i] * B[k] * B[j]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < N/2; i++) {
        ans = max(ans, dp[i][i+N/2-1]);
    }
    printf("%d\n", ans);
    return 0;
}
