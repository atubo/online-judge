// https://www.luogu.org/problemnew/show/P3208
// [HNOI2010]矩阵

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;
int N, M, P;
int A[MAXN][MAXN];
int B[MAXN][MAXN];
int sol[MAXN][MAXN];
int X[MAXN];

struct Limit {
    int l, r;
    bool merge(int l2, int r2) {
        if (r2 < l2) return false;
        if (r2 < l || l2 > r) return false;
        int rn = min(r, r2);
        int ln = max(l, l2);
        l = ln;
        r = rn;
        return true;
    }
} limits[MAXN][MAXN];

void solve() {
    for (int j = 0; j < M; j++) {
        sol[0][j] = X[j];
    }
    for (int i = 1; i < N; i++) {
        sol[i][0] = limits[M-1][i].l;
        for (int j = 1; j < M; j++) {
            sol[i][j] = A[i][j] - sol[i-1][j-1] - sol[i-1][j] - sol[i][j-1];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M-1; j++) {
            printf("%d ", sol[i][j]);
        }
        printf("%d\n", sol[i][M-1]);
    }
}

bool dfs(int j, int x) {
    if (j == M) return true;
    X[j] = x;
    int pj = (j & 1 ? -1 : 1);
    for (int i = 1; i < N; i++) {
        int pi = (i & 1 ? -1 : 1);
        int r = B[i][j] - pi*pj*X[0] + pi*X[j];
        limits[j][i] = limits[j-1][i];
        if (pj > 0) {
            if (!limits[j][i].merge(-r, P-r-1)) return false;
        } else {
            if (!limits[j][i].merge(r-P+1, r)) return false;
        }
    }
    for (int x2 = 0; x2 < P; x2++) {
        if (dfs(j+1, x2)) return true;
    }
    return false;
}


int main() {
    scanf("%d%d%d", &N, &M, &P);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    int line[MAXN] = {0};
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            if (j == 1) line[j] = A[i][j];
            else line[j] = line[j-2] + A[i][j];
            B[i][j] = -B[i-1][j] + line[j] - line[j-1];
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 1; j < N; j++) {
            limits[i][j] = {0, P-1};
        }
    }
    for (int x0 = 0; x0 < P; x0++) {
        X[0] = x0;
        for (int x1 = 0; x1 < P; x1++) {
            if (dfs(1, x1)) {
                solve();
                return 0;
            }
        }
    }

    return 0;
}
