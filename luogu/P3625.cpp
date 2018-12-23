// https://www.luogu.org/problemnew/show/P3625
// [APIO2009]采油区域

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1510;
int M, N, K;
int A[MAXN][MAXN];
int ps[MAXN][MAXN], B[MAXN][MAXN];
int SE[MAXN][MAXN], SW[MAXN][MAXN], NE[MAXN][MAXN], NW[MAXN][MAXN];
int ROW[MAXN], COL[MAXN];
int RR[MAXN][MAXN], CR[MAXN][MAXN];

int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

int main() {
    scanf("%d%d%d", &M, &N, &K);
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &A[i][j]);
            ps[i][j] = int64_t(A[i][j]) + ps[i-1][j] + ps[i][j-1]
                - ps[i-1][j-1];
        }
    }
    for (int i = 1; i <= M-K+1; i++) {
        for (int j = 1; j <= N-K+1; j++) {
            B[i][j] = int64_t(ps[i+K-1][j+K-1]) - ps[i-1][j+K-1]
                - ps[i+K-1][j-1] + ps[i-1][j-1];
        }
    }
    for (int i = K; i <= M; i++) {
        for (int j = K; j <= N; j++) {
            SE[i][j] = max3(SE[i-1][j], SE[i][j-1], B[i-K+1][j-K+1]);
        }
    }
    for (int i = K; i <= M; i++) {
        for (int j = N-K+1; j >= 1; j--) {
            SW[i][j] = max3(SW[i-1][j], SW[i][j+1], B[i-K+1][j]);
        }
    }
    for (int i = M-K+1; i >= 1; i--) {
        for (int j = K; j <= N; j++) {
            NE[i][j] = max3(NE[i+1][j], NE[i][j-1], B[i][j-K+1]);
        }
    }
    for (int i = M-K+1; i >= 1; i--) {
        for (int j = N-K+1; j >= 1; j--) {
            NW[i][j] = max3(NW[i+1][j], NW[i][j+1], B[i][j]);
        }
    }
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            ROW[i] = max(ROW[i], B[i][j]);
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            COL[i] = max(COL[i], B[j][i]);
        }
    }
    for (int l = 1; l <= N-K+1; l++) {
        for (int r = l+K-1; r <= N; r++) {
            CR[l][r] = max(CR[l][r-1], COL[r-K+1]);
        }
    }
    for (int t = 1; t <= M-K+1; t++) {
        for (int b = t+K-1; b <= M; b++) {
            RR[t][b] = max(RR[t][b-1], ROW[b-K+1]);
        }
    }

    int ans = 0;
    for (int i = K; i < M-K+1; i++) {
        for (int j = K; j < N-K+1; j++) {
            ans = max(ans, SE[i][j] + NE[i+1][j] + CR[j+1][N]);
            ans = max(ans, SE[i][j] + SW[i][j+1] + RR[i+1][M]);
            ans = max(ans, CR[1][j] + SW[i][j+1] + NW[i+1][j+1]);
            ans = max(ans, RR[1][i] + NE[i+1][j] + NW[i+1][j+1]);
        }
    }

    for (int l = K; l <= N; l++) {
        for (int r = l+K; r <= N-K; r++) {
            ans = max(ans, CR[1][l]+CR[l+1][r]+CR[r+1][N]);
        }
    }

    for (int t = K; t <= M; t++) {
        for (int b = t+K; b <= M-K; b++) {
            ans = max(ans, RR[1][t]+RR[t+1][b]+RR[b+1][M]);
        }
    }

    printf("%d", ans);

    return 0;
}
