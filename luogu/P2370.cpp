// https://www.luogu.org/problemnew/show/P2370
// yyy2015c01的U盘

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int N, P, S;
int W[MAXN], V[MAXN];

bool solve(int L) {
    vector<int> dp(1001, -1);
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        int w = W[i], v = V[i];
        if (w > L) continue;
        for (int j = S; j >= 0; j--) {
            if (j >= w && dp[j-w] >= 0) {
                dp[j] = max(dp[j], dp[j-w] + v);
            }
        }
    }
    int ret = 0;
    for (int j = S; j >= 0; j--) {
        ret = max(ret, dp[j]);
    }
    return ret >= P;
}

int main() {
    scanf("%d%d%d", &N, &P, &S);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &W[i], &V[i]);
    }
    int lo = 0, hi = 1001;
    if (!solve(hi)) {
        printf("No Solution!\n");
        return 0;
    }
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (solve(mid)) hi = mid;
        else lo = mid;
    }
    printf("%d\n", hi);
    return 0;
}
