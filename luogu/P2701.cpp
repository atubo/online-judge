// https://www.luogu.org/problemnew/show/P2701
// [USACO5.3]巨大的牛棚Big Barn

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int N, T;
int F[MAXN][MAXN], dp[MAXN][MAXN];

int min3(int a, int b, int c) {
    return min(a, min(b, c));
}

int main() {
    scanf("%d%d", &N, &T);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            F[i][j] = 1;
        }
    }
    for (int i = 0; i < T; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        F[x][y] = 0;
    }
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (F[i][j]) {
                dp[i][j] = 1 + min3(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]);
                ans = max(dp[i][j], ans);
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}
