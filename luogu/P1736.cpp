// https://www.luogu.org/problem/show?pid=1736
// 创意吃鱼法
#include <bits/stdc++.h>
using std::min;
using std::max;
using std::swap;

const int MAXN = 2510;
int A[MAXN][MAXN];
int dp[MAXN][MAXN], left[MAXN][MAXN], up[MAXN][MAXN];
int N,M;

void init() {
    for (int i = 0; i < N; i++) {
        memset(left[i], 0, sizeof(int)*M);
        memset(up[i], 0, sizeof(int)*M);
        memset(dp[i], 0, sizeof(int)*M);
    }
}

int solve() {
    init();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] == 0) {
                left[i][j] = 1 + (j > 0 ? left[i][j-1] : 0);
                up[i][j] = 1 + (i > 0 ? up[i-1][j] : 0);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] == 1) {
                dp[i][j] = 1;
                if (i > 0 && j > 0) {
                    dp[i][j] = 1 + min(dp[i-1][j-1], min(up[i-1][j], left[i][j-1]));
                }
                ans = max(ans, dp[i][j]);
            }
        }
    }
    return ans;
}


int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    int ans = solve();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M/2; j++) {
            swap(A[i][j], A[i][M-1-j]);
        }
    }
    ans = max(ans, solve());
    printf("%d\n", ans);
    return 0;
}
