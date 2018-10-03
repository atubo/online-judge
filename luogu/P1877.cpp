// https://www.luogu.org/problemnew/show/P1877
// [HAOI2012]音量调节

#include <bits/stdc++.h>
using namespace std;

const int MAXLEVEL = 1010;
vector<bool> dp(MAXLEVEL), dp_next(MAXLEVEL);

int main() {
    int n, b, maxl;
    scanf("%d%d%d", &n, &b, &maxl);
    dp[b] = true;
    for (int i = 0; i < n; i++) {
        int c;
        scanf("%d", &c);
        dp_next.assign(maxl+1, false);
        for (int j = 0; j <= maxl; j++) {
            if (dp[j]) {
                if (j-c >= 0) dp_next[j-c] = true;
                if (j+c <= maxl) dp_next[j+c] = true;
            }
        }
        swap(dp, dp_next);
    }
    int ans = maxl;
    for (; ans >= 0; ans--) {
        if (dp[ans]) break;
    }
    printf("%d", ans);
    return 0;
}
