// https://www.luogu.org/problem/show?pid=2224
// [HNOI2001]产品加工

#include <bits/stdc++.h>
using namespace std;

int dp[30010];
int t[6010][3];
int mx;

int main() {
    int N;
    scanf("%d", &N);
    memset(dp, 0x7F, sizeof(dp));
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &t[i][0], &t[i][1], &t[i][2]);
    }
    for (int i = 0; i < N; i++) {
        int a, b, c;
        a = t[i][0] == 0 ? INT_MAX: t[i][0];
        b = t[i][1] == 0 ? INT_MAX: t[i][1];
        c = t[i][2] == 0 ? INT_MAX: t[i][2];
        mx += min(min(a, b), c);
        for (int j = mx; j >= 0; j--) {
            if (b != INT_MAX) dp[j] += b;
            else dp[j] = 0x7F7F7F7F;
            if (j >= a) dp[j] = min(dp[j], dp[j-a]);
            if (j >= c) dp[j] = min(dp[j], dp[j-c]+c);
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i <= mx; i++) {
        ans = min(ans, max(i, dp[i]));
    }
    printf("%d\n", ans);
    return 0;
}
