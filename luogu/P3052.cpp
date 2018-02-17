// https://www.luogu.org/problemnew/show/P3052
// [USACO12MAR]摩天大楼里的奶牛Cows in a Skyscraper

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
int N, W;
int C[MAXN];
int sm[1<<18], dp[1<<18], g[1<<18];

void init() {
    for (int s = 1; s < (1<<N); s++) {
        for (int i = 0; i < N; i++) {
            if ((s>>i) & 1) {
                sm[s] += C[i];
            }
        }
    }
}

void mobius() {
    for (int k = 0; k < N; k++) {
        int s = ((1<<N)-1) ^ (1<<k);
        int *h = g + (1<<k);
        for (int j = s; j; j = (j-1)&s) {
            h[j] = max(h[j], g[j]);
        }
    }
}

int solve() {
    // k = 1
    for (int s = 0; s < (1<<N); s++) {
        g[s] = (sm[s] <= W ? sm[s] : 0);
    }
    if (g[(1<<N)-1] > 0) return 1;
    mobius();
    for (int k = 2; k <= N; k++) {
        for (int s = 0; s < (1<<N); s++) {
            g[s] = (sm[s] - g[s] <= W ? sm[s] : 0);
        }
        if (g[(1<<N)-1] > 0) return k;
        mobius();
    }
    assert(0);
    return -1;
}

int main() {
    scanf("%d%d", &N, &W);
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }
    init();
    int ret = solve();
    printf("%d", ret);
    return 0;
}
