// https://www.luogu.org/problemnew/show/P3607
// [USACO17JAN]Subsequence Reversal序列反转

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 52;
int N;
int A[MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];

int solve(int i, int j, int k, int m) {
    if (k > m) return -1e8;
    if (i > j) return 0;
    if (dp[i][j][k][m] >= 0) return dp[i][j][k][m];
    if (i == j) return (A[i] >= k && A[j] <= m);
    int &ret = dp[i][j][k][m] = 0;
    ret = max(ret, solve(i+1, j-1, k, m));
    if (A[j] >= k) ret = max(ret, solve(i+1, j-1, A[j], m) + 1);
    if (A[i] <= m) ret = max(ret, solve(i+1, j-1, k, A[i]) + 1);
    if (A[j] >= k && A[i] <= m) {
        ret = max(ret, solve(i+1, j-1, A[j], A[i]) + 2);
    }
    ret = max(ret, solve(i+1, j, k, m));
    if (A[i] >= k) ret = max(ret, solve(i+1, j, A[i], m) + 1);
    ret = max(ret, solve(i, j-1, k, m));
    if (A[j] <= m) ret = max(ret, solve(i, j-1, k, A[j]) + 1);
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    int ans = solve(0, N-1, 0, 50);
    printf("%d\n", ans);

    return 0;
}
