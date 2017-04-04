// https://www.luogu.org/problem/show?pid=2769
// 猴子上树

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;
int X[MAXN], Y[MAXN];
int M, N;
int64_t dp[MAXN];

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

    dp[0] = 0;
    for (int i = 1; i <= M; i++) {
        dp[i] = INT_MAX;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = min(M, i); j >= 1; j--) {
            dp[j] = min(dp[j], dp[j-1]) + dist(i, j);
        }
        dp[0] = INT_MAX;
    }

    printf("%lld\n", dp[M]);
    return 0;
}
