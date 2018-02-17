// https://www.luogu.org/problemnew/show/P3052
// [USACO12MAR]摩天大楼里的奶牛Cows in a Skyscraper

#include <bits/stdc++.h>
using namespace std;

#define MAX(a, b) (a>b ? a: b)

const int MAXN = 20;
int N, W;
int C[MAXN];
int sm[1<<18], dp[1<<18], g[1<<18], gp[1<<18];
int fpk[MAXN][1<<18];

void init() {
    for (int s = 1; s < (1<<N); s++) {
        for (int i = 0; i < N; i++) {
            if ((s>>i) & 1) {
                sm[s] += C[i];
            }
        }
    }
}

void mobius(int *f, int *fp) {
    for (int s = 0; s < (1<<N); s++) {
        fpk[0][s] = f[s];
        for (int k = 1; k <= N; k++) {
            fpk[k][s] = fpk[k-1][s];
            if ((s>>(k-1)) & 1) {
                fpk[k][s] = MAX(fpk[k][s], fpk[k-1][s&(~(1<<(k-1)))]);
            }
        }
        fp[s] = fpk[N][s];
    }
}

int solve() {
    // k = 1
    for (int s = 0; s < (1<<N); s++) {
        g[s] = (sm[s] <= W ? sm[s] : 0);
    }
    if (g[(1<<N)-1] > 0) return 1;
    mobius(g, gp);
    for (int k = 2; k <= N; k++) {
        for (int s = 0; s < (1<<N); s++) {
            g[s] = (sm[s] - gp[s] <= W ? sm[s] : 0);
        }
        if (g[(1<<N)-1] > 0) return k;
        mobius(g, gp);
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
