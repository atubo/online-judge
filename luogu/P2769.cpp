// https://www.luogu.org/problem/show?pid=2769
// 猴子上树

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;
int X[MAXN], Y[MAXN];
int M, N;
int64_t dp[MAXN][MAXN];

int dist(int i, int j) {
    return abs(X[i] - Y[j]);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &X[i]);
    }
    scanf("%d", &M);
    for (int i = 1; i <= M; i++) {
        scanf("%d", &Y[i]);
    }

    sort(X + 1, X + N + 1);
    sort(Y + 1, Y + M + 1);

    dp[0][0] = 0;
    for (int i = 1; i <= N; i++) {
        dp[i][0] = INT_MAX;
        for (int j = 1; j <= M; j++) {
            if (j > i) break;
            dp[i][j] =  dp[i-1][j-1];
            if (i >= j + 1) dp[i][j] = min(dp[i][j], dp[i-1][j]);
            dp[i][j] += dist(i, j);
        }
    }
    printf("%lld\n", dp[N][M]);
    return 0;
}
