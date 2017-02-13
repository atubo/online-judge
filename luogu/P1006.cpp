// https://www.luogu.org/problem/show?pid=1006
// 传纸条

#include <bits/stdc++.h>
using namespace std;

int dp[52][52][52][52];
int M, N;
int A[52][52];

bool inRange(int i, int j) {
    return (0 <= i && i < M && 0 <= j && j < N);
}

bool feasible(int i, int j, int k, int l) {
    return (inRange(i, j) && inRange(k, l) && dp[i][j][k][l] >= 0);
}

void search(int i, int j, int k, int l,
            int pi, int pj, int pk, int pl) {
    if (feasible(pi, pj, pk, pl)) {
        dp[i][j][k][l] = max(dp[i][j][k][l],
                             dp[pi][pj][pk][pl] + A[i][j] + A[k][l]);
    }
}

int main() {
    scanf("%d %d", &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0][0][0] = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                for (int l = 0; l < N; l++) {
                    if ((i == 0 && j == 0 && k == 0 && l == 0) ||
                        (i == M-1 && j == N-1 && k == M-1 && l == N-1)) continue;
                    if (i == k && j == l) continue;
                    search(i, j, k, l, i-1, j, k-1, l);
                    search(i, j, k, l, i-1, j, k, l-1);
                    search(i, j, k, l, i, j-1, k-1, l);
                    search(i, j, k, l, i, j-1, k, l-1);
                }
            }
        }
    }

    printf("%d\n", dp[M-1][N-2][M-2][N-1]);
    return 0;
}
