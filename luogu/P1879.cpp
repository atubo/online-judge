// https://www.luogu.org/problemnew/show/P1879
// [USACO06NOV]玉米田Corn Fields

#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000000;
int M, N;
int field[14];
int dp[14][1<<12];

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < N; j++) {
            int x;
            scanf("%d", &x);
            if (!x) field[i] |= (1<<j);
        }
    }

    dp[0][0] = 1;
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < (1<<N); j++) {
            if (dp[i-1][j] == 0) continue;
            for (int k = 0; k < (1<<N); k++) {
                if ((k & field[i]) || (k & j) || (k & (k<<1))) continue;
                (dp[i][k] += dp[i-1][j]) %= MOD;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < (1<<N); i++) {
        (ans += dp[M][i]) %= MOD;
    }

    printf("%d\n", ans);
    return 0;
}
