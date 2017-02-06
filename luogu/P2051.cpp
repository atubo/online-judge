// https://www.luogu.org/problem/show?pid=2051
// [AHOI2009]中国象棋

#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 9999973;

int64_t add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

const int MAXN = 110;
int64_t f[MAXN][MAXN][MAXN];

int main() {
    int n, m;
    cin >> n >> m;
    f[0][0][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; j + k <= n; k++) {
                f[i][j][k] = f[i-1][j][k];
                if (j >= 1) {
                    f[i][j][k] = add(f[i][j][k], mul(f[i-1][j-1][k], n-j-k+1));
                }
                if (k >= 1) {
                    f[i][j][k] = add(f[i][j][k], mul(f[i-1][j+1][k-1], j+1));
                    f[i][j][k] = add(f[i][j][k], mul(f[i-1][j][k-1], (n-j-k+1)*j));
                }
                if (j >= 2) {
                    f[i][j][k] = add(f[i][j][k], mul(f[i-1][j-2][k],
                                                     (n-j-k+2)*(n-j-k+1)/2));
                }
                if (k >= 2) {
                    f[i][j][k] = add(f[i][j][k], mul(f[i-1][j+2][k-2], (j+2)*(j+1)/2));
                }
            }
        }
    }

    int64_t ans = 0;
    for (int j = 0; j <= n; j++) {
        for (int k = 0; j + k <= n; k++) {
            ans = add(ans, f[m][j][k]);
        }
    }
    cout << ans << endl;
    return 0;
}
