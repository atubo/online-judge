// https://www.luogu.org/problem/show?pid=2258
// 子矩阵

#include <bits/stdc++.h>
using namespace std;

int dp[18][18];
int N, M, R, C;
int A[16][16];

int col(const vector<int> &s, int m) {
    int ret = 0;
    for (int i = 1; i < R; i++) {
        ret += abs(A[s[i]][m] - A[s[i-1]][m]);
    }
    return ret;
}

int row(const vector<int> &s, int m, int m2) {
    int ret = 0;
    for (int i = 0; i < R; i++) {
        ret += abs(A[s[i]][m] - A[s[i]][m2]);
    }
    return ret;
}

int solve(const vector<int> &s) {
    memset(dp, 0x7f, sizeof(dp));
    int ret = INT_MAX;
    for (int m = 0; m < M; m++) {
        dp[m][1] = col(s, m);
        for (int k = 2; k <= C; k++) {
            for (int m2 = k-2; m2 < m; m2++) {
                dp[m][k] = min(dp[m][k], dp[m2][k-1] + row(s, m, m2) + dp[m][1]);
            }
        }
        ret = min(ret, dp[m][C]);
    }
    return ret;
}

void convert(int x, vector<int> &s) {
    int i = 0;
    for (int j = 0; j < N; j++) {
        if ((x >> j) & 1) s[i++] = j;
    }
}

int main() {
    scanf("%d%d%d%d", &N, &M, &R, &C);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    int ret = INT_MAX;
    vector<int> s(R);
    for (int i = 0; i < (1 << N); i++) {
        if (__builtin_popcount(i) == R) {
            convert(i, s);
            ret = min(ret, solve(s));
        }
    }
    printf("%d\n", ret);
    return 0;
}
