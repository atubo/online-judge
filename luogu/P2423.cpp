// https://www.luogu.org/problem/show?pid=2423
// 双塔

#include <bits/stdc++.h>
using namespace std;

int N;
int dp[2][1001];

int main() {
    scanf("%d", &N);
    int idx = 0;
    memset(dp[0], -1, sizeof(dp[0]));
    dp[0][0] = 0;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        idx = idx ^ 1;
        memset(dp[idx], -1, sizeof(dp[idx]));
        for (int d = 0; d <= 1000; d++) {
            if (dp[idx^1][d] >= 0) {
                dp[idx][d] = max(dp[idx][d], dp[idx^1][d]);
                if (d + x <= 1000) {
                    dp[idx][d+x] = max(dp[idx][d+x], dp[idx^1][d]);
                }
                if (d >= x) {
                    dp[idx][d-x] = max(dp[idx][d-x], dp[idx^1][d] + x);
                } else {
                    dp[idx][x-d] = max(dp[idx][x-d], dp[idx^1][d] + d);
                }
            }
        }
    }
    int ret = dp[idx][0];
    if (ret > 0) printf("%d\n", ret);
    else printf("Impossible\n");
    return 0;
}
