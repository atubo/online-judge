// https://www.luogu.org/problemnew/show/P2392
// kkksc03考前临时抱佛脚

#include <bits/stdc++.h>
using namespace std;

int solve(int N) {
    vector<int> dp(1201);
    dp[0] = true;
    int tot = 0;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        tot += x;
        for (int j = tot; j >= 0; j--) {
            if (j >= x) dp[j] |= dp[j-x];
        }
    }
    int ret = INT_MAX;
    for (int j = tot; j >= 0; j--) {
        if (dp[j]) ret = min(ret, max(j, tot-j));
    }
    return ret;
}

int main() {
    int A, B, C, D;
    scanf("%d%d%d%d", &A, &B, &C, &D);
    int ret = solve(A) + solve(B) + solve(C) + solve(D);
    printf("%d\n", ret);
    return 0;
}
