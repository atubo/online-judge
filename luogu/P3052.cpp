// https://www.luogu.org/problemnew/show/P3052
// [USACO12MAR]摩天大楼里的奶牛Cows in a Skyscraper

#include <bits/stdc++.h>
using namespace std;
using Pii = pair<int, int>;

const int MAXN = 20;
int N, W;
int C[MAXN];
int dp[1<<18];

int solve(int mask) {
    if (mask == 0) return 0;
    if (dp[mask] > 0) return dp[mask];
    int &ret = dp[mask];
    int wt = 0;
    for (int i = 0; i < N; i++) {
        if ((mask >> i) & 1) wt += C[i];
    }
    if (wt <= W) return (ret = 1);
    ret = INT_MAX;
    for (int s = mask; s; s = (s-1) & mask) {
        if (s == mask) continue;
        int t = (mask ^ s) & mask;
        int c = solve(s) + solve(t);
        if (c < ret) {
            ret = c;
        }
    }
    return ret;
}

int main() {
    scanf("%d%d", &N, &W);
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }
    int ret = solve((1<<N)-1);
    printf("%d", ret);
    return 0;
}
