// https://www.luogu.org/problem/P4067
// [SDOI2016]储能表

#include <bits/stdc++.h>
using namespace std;

int64_t f[62][2][2][2], g[62][2][2][2];

int64_t mul(int64_t a, int64_t b, int64_t p) {
    return ((a % p) * (b % p)) % p;
}

int64_t solve(int64_t n, int64_t m, int64_t k, int64_t p) {
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    g[61][1][1][1] = 1;
    for (int i = 60; i >= 0; i--) {
        int x = (n >> i) & 1;
        int y = (m >> i) & 1;
        int z = (k >> i) & 1;
        for (int aa = 0; aa < 2; aa++) {
            for (int bb = 0; bb < 2; bb++) {
                for (int cc = 0 ; cc < 2; cc++) {
                    for (int xx = 0; xx < 2; xx++) {
                        for (int yy = 0; yy < 2; yy++) {
                            int zz = xx ^ yy;
                            if ((aa && xx > x) ||
                                (bb && yy > y) ||
                                (cc && zz < z)) continue;
                            int a = aa && (xx == x);
                            int b = bb && (yy == y);
                            int c = cc && (zz == z);
                            (g[i][a][b][c] += g[i+1][aa][bb][cc]) %= p;
                            (f[i][a][b][c] += f[i+1][aa][bb][cc]) %= p;
                            (f[i][a][b][c] += 
                             mul(mul(zz-z+p, 1LL<<i, p),
                                 g[i+1][aa][bb][cc],
                                 p)) %= p;
                        }
                    }
                }
            }
        }
    }

    return f[0][0][0][0];
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int64_t n, m, k, p;
        scanf("%ld%ld%ld%ld", &n, &m, &k, &p);
        printf("%ld\n", solve(n, m, k, p));
    }
    return 0;
}
