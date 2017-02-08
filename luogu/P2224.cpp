// https://www.luogu.org/problem/show?pid=2224
// [HNOI2001]产品加工

#include <bits/stdc++.h>
using namespace std;

int dp[30010];
int mx;

int main() {
    int N;
    scanf("%d", &N);
    memset(dp, 0x7F, sizeof(dp));
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        mx += max(a, c);
        for (int j = mx; j >= 0; j--) {
            int tmp = 0x7F7F7F7F;
            if (a && j >= a) tmp = min(tmp, dp[j-a]);
            if (b) tmp = min(tmp, dp[j] + b);
            if (c && j >= c) tmp = min(tmp, dp[j-c]+c);
            dp[j] = tmp;
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i <= mx; i++) {
        ans = min(ans, max(i, dp[i]));
    }
    printf("%d\n", ans);
    return 0;
}
