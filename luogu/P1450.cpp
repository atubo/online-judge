// https://www.luogu.org/problemnew/show/P1450
// [HAOI2008]硬币购物

#include <bits/stdc++.h>
using namespace std;

const int MAXS = 100010;
int64_t dp[MAXS];
int C[4], T;
int D[4], S;

void solveDp() {
    dp[0] = 1;
    for (int i = 0; i < 4; i++) {
        for (int k = C[i]; k <= 100000; k++) {
            dp[k] += dp[k-C[i]];
        }
    }
}

int64_t count(int k) {
    int idx = S;
    int sgn = 1;
    for (int i = 0; i < 4; i++) {
        if ((k >> i) & 1) {
            idx -= C[i] * (D[i]+1);
            sgn = -sgn;
        }
    }
    if (idx < 0) return 0;
    return sgn * dp[idx];
}

void solve() {
    int64_t ans = 0;
    for (int k = 0; k < 16; k++) {
        ans += count(k);
    }
    printf("%lld\n", ans);
}

int main() {
    scanf("%d%d%d%d%d", &C[0], &C[1], &C[2], &C[3], &T);
    solveDp();
    while (T--) {
        scanf("%d%d%d%d%d", &D[0], &D[1], &D[2], &D[3], &S);
        solve();
    }

    return 0;
}
