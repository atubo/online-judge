// https://www.luogu.org/problemnew/show/P3188
// [HNOI2007]梦幻岛宝珠

#include <bits/stdc++.h>
using namespace std;

struct Item {
    int w, v;
};

const int MASK = 1023;
int N, W;
int dp[32][1024];
vector<vector<Item>> items(32);

int main() {
    while (scanf("%d%d", &N, &W) > 0 && N != -1) {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < 32; i++) items[i].clear();
        for (int i = 0; i < N; i++) {
            int w, v;
            scanf("%d%d", &w, &v);
            int b = 0;
            while (!(w&1)) {
                w >>= 1;
                b++;
            }
            items[b].push_back({w, v});
        }
        for (const auto &item: items[0]) {
            for (int k = MASK; k >= item.w; k--) {
                dp[0][k] = max(dp[0][k], dp[0][k-item.w] + item.v);
            }
        }
        for (int k = 1; k <= MASK; k++) {
            dp[0][k] = max(dp[0][k], dp[0][k-1]);
        }
        int ans = 0;
        for (int i = 0; i <= min(W, MASK); i++) {
            ans = max(ans, dp[0][i]);
        }
        for (int i = 1; i < 32; i++) {
            int u = (W >> (i-1)) & 1;
            for (int j = 0; j <= min(MASK, W>>i); j++) {
                dp[i][j] = dp[i-1][((j<<1)&MASK)|u];
            }
            for (const auto &item: items[i]) {
                for (int j = min(MASK, W>>i); j >= item.w; j--) {
                    dp[i][j] = max(dp[i][j], dp[i][j-item.w] + item.v);
                }
            }
            for (int j = 1; j <= MASK; j++) {
                dp[i][j] = max(dp[i][j], dp[i][j-1]);
            }
            ans = max(ans, dp[i][MASK]);
        }

        printf("%d\n", ans);
    }

    return 0;
}
