// https://www.luogu.org/problemnew/show/P4077
// [SDOI2016]硬币游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30010;
int T;
int N, MAXQ;
int A[MAXN];
int SG[17][17], flag[MAXN];

void build() {
    for (int i = 0; i <= 16; i++) {
        for (int j = 0; j <= 16; j++) {
            memset(flag, 0, sizeof(flag));
            for (int p = 1; p <= j; p++) {
                for (int q = 1; q <= min(MAXQ, j/p); q++) {
                    int o = -1;
                    for (int k = 1; k <= q; k++) {
                        o = (o == -1 ? SG[i][j-k*p] : o ^ SG[i][j-k*p]);
                    }
                    if (o != -1) flag[o] = 1;
                }
            }
            for (int p = 1; p <= i; p++) {
                for (int q = 1; q <= min(MAXQ, i/p); q++) {
                    int o = -1;
                    for (int k = 1; k <= q; k++) {
                        o = (o == -1 ? SG[i-k*p][j] : o ^ SG[i-k*p][j]);
                    }
                    if (o != -1) flag[o] = 1;
                }
            }
            for (int o = 0; o < MAXN; o++) {
                if (flag[o] == 0) {
                    SG[i][j] = o;
                    break;
                }
            }
        }
    }
}

void calcxy(int s, int &x, int &y) {
    x = y = 0;
    while (s % 2 == 0) {
        s /= 2;
        x++;
    }
    while (s % 3 == 0) {
        s /= 3;
        y++;
    }
}

void solve() {
    scanf("%d%d", &N, &MAXQ);
    build();
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        int v;
        scanf("%d", &v);
        if (v == 1) continue;
        int x, y;
        calcxy(i, x, y);
        ans ^= SG[x][y];
    }
    printf(ans > 0 ? "win\n" : "lose\n");
}

int main() {
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
