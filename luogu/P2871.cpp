// https://www.luogu.org/problemnew/show/P2871
// [USACO07DEC]手链Charm Bracelet

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 12890;
const int MAXN = 3412;
int N, M;
int dp[MAXM];

int main() {
    scanf("%d%d", &N, &M);
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        int c, w;
        scanf("%d%d", &c, &w);
        for (int j = M; j >= c; j--) {
            if (dp[j-c] != -1) {
                dp[j] = max(dp[j], dp[j-c] + w);
            }
        }
    }
    int ans = -1;
    for (int i = 0; i <= M; i++) {
        ans = max(ans, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}
