// https://www.luogu.org/problem/show?pid=2216
// [HAOI2007] 理想的正方形

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int f[MAXN][MAXN][11];
int g[MAXN][MAXN][11];

int N, M, L;
int maxk;

int max4(int a, int b, int c, int d) {
    return max(max(a, b), max(c, d));
}

int min4(int a, int b, int c, int d) {
    return min(min(a, b), min(c, d));
}

void build() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int x;
            scanf("%d", &x);
            f[i][j][0] = g[i][j][0] = x;
        }
    }

    maxk = 0;
    while ((1 << (1+maxk)) < L) maxk++;

    for (int k = 1; k <= maxk; k++) {
        int s = (1 << k);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (i + s <= N && j + s <= M) {
                    f[i][j][k] = max4(f[i][j][k-1],
                                      f[i+s/2][j][k-1],
                                      f[i][j+s/2][k-1],
                                      f[i+s/2][j+s/2][k-1]);
                    g[i][j][k] = min4(g[i][j][k-1],
                                      g[i+s/2][j][k-1],
                                      g[i][j+s/2][k-1],
                                      g[i+s/2][j+s/2][k-1]);
                }
            }
        }
    }
}

int diff(int i, int j) {
    int s = (1 << maxk);
    int high = max4(f[i][j][maxk],
                    f[i+L-s][j][maxk],
                    f[i][j+L-s][maxk],
                    f[i+L-s][j+L-s][maxk]);
    int low = min4(g[i][j][maxk],
                   g[i+L-s][j][maxk],
                   g[i][j+L-s][maxk],
                   g[i+L-s][j+L-s][maxk]);
    return high - low;
}

int main() {
    scanf("%d %d %d", &N, &M, &L);
    build();

    int ans = INT_MAX;
    for (int i = 0; i + L <= N; i++) {
        for (int j = 0; j + L <= M; j++) {
            ans = min(ans, diff(i, j));
        }
    }
    printf("%d\n", ans);

    return 0;
}
