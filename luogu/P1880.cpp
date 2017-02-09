// https://www.luogu.org/problem/show?pid=1880
// 石子合并

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;
int dp[MAXN][MAXN];
int A[MAXN], ps[MAXN];
int N;

int solve1() {
    for (int i = 1; i <= N; i++) {
        dp[i][i] = 0;
    }
    for (int len = 2; len <= N/2; len++) {
        for (int i = 1; i <= N-len; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + ps[j]-ps[i-1]);
            }
        }
    }
    int ans = INT_MAX;
    for (int i = 1; i <= N/2; i++) {
        ans = min(ans, dp[i][i+N/2-1]);
    }
    return ans;
}

int solve2() {
    for (int i = 1; i <= N; i++) {
        dp[i][i] = 0;
    }
    for (int len = 2; len <= N/2; len++) {
        for (int i = 1; i <= N-len; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MIN;
            for (int k = i; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j] + ps[j]-ps[i-1]);
            }
        }
    }
    int ans = INT_MIN;
    for (int i = 1; i <= N/2; i++) {
        ans = max(ans, dp[i][i+N/2-1]);
    }
    return ans;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        A[i+N] = A[i];
    }
    N *= 2;
    for (int i = 1; i <= N; i++) {
        ps[i] = A[i] + ps[i-1];
    }
    printf("%d\n%d\n", solve1(), solve2());
    return 0;
}
