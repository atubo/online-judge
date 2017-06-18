// https://www.luogu.org/problem/show?pid=1133
// 教主的花园

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int V[MAXN][3];
int dp[2][16];
int N;

void init() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 16; j++) {
            dp[i][j] = INT_MIN;
        }
    }
}

int f(int prev, int curr) {
    return prev * 4 + curr;
}

void solve() {
    for (int i = 2; i < N; i++) {
        int curr = i & 1;
        int prev = (i-1) & 1;
        dp[curr][f(1, 2)] = V[i][2] + dp[prev][f(2, 1)];
        dp[curr][f(0, 2)] = V[i][2] + max(dp[prev][f(2, 0)], dp[prev][f(1, 0)]);
        dp[curr][f(2, 1)] = V[i][1] + max(dp[prev][f(1, 2)], dp[prev][f(0, 2)]);
        dp[curr][f(0, 1)] = V[i][1] + max(dp[prev][f(2, 0)], dp[prev][f(1, 0)]);
        dp[curr][f(2, 0)] = V[i][0] + max(dp[prev][f(1, 2)], dp[prev][f(0, 2)]);
        dp[curr][f(1, 0)] = V[i][0] + dp[prev][f(0, 1)];
    }
}

int max3(int a, int b, int c) {
    return max(max(a, b), c);
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &V[i][0], &V[i][1], &V[i][2]);
    }

    // 10
    init();
    dp[1][f(0, 1)] = V[0][0] + V[1][1];
    dp[1][f(0, 2)] = V[0][0] + V[1][2];
    solve();
    int ret = max3(dp[1][f(0, 1)], dp[1][f(0, 2)], dp[1][f(1, 2)]);

    // 20-30
    init();
    dp[1][f(1, 2)] = V[0][1] + V[1][2];
    solve();
    ret = max(ret, max(dp[1][f(0, 2)], dp[1][f(1, 2)]));

    // 20-10
    init();
    dp[1][f(1, 0)] = V[0][1] + V[1][0];
    solve();
    ret = max(ret, max(dp[1][f(1, 0)], dp[1][f(2, 0)]));

    // 30
    init();
    dp[1][f(2, 1)] = V[0][2] + V[1][1];
    dp[1][f(2, 0)] = V[0][2] + V[1][0];
    solve();
    ret = max(ret, max3(dp[1][f(2, 0)], dp[1][f(1, 0)], dp[1][f(2, 1)]));

    printf("%d\n", ret);
    return 0;
}
