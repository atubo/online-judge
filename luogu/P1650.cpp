// https://www.luogu.org/problem/show?pid=1650
// 赛马

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2010;
int A[MAXN], B[MAXN];
int N;
int dp[MAXN][MAXN];

int sgn(int d) {
    return d > 0 ? 1 : (d < 0 ? -1 : 0);
}

int solve(int i, int j) {
    if (dp[i][j] != -1) return dp[i][j];
    int &ret = dp[i][j];
    if (j == N-1) {
        ret = sgn(A[i]-B[j]);
        return ret;
    }
    if (A[i] > B[j]) {
        ret = 1 + solve(i+1, j+1);
    } else if (A[i] < B[j]) {
        ret = solve(i, j+1) - 1;
    } else {
        ret = max(solve(i+1, j+1), solve(i, j+1) - 1);
    }
    return ret;
}
    

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    sort(A, A+N, greater<int>());
    sort(B, B+N, greater<int>());
    memset(dp, -1, sizeof(dp));

    printf("%d\n", 200 * solve(0, 0));
    return 0;
}
