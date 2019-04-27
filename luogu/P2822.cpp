// https://www.luogu.org/problemnew/show/P2822
// 组合数问题

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2048;
int T, K;
int N, M;
int C[MAXN][MAXN], D[MAXN][MAXN], S[MAXN][MAXN];

void build() {
    C[0][0] = 1 % K;
    for (int i = 1; i < MAXN; i++) {
        C[i][0] = 1 % K;
        for (int j = 1; j < MAXN; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % K;
        }
    }

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j <= i; j++) {
            D[i][j] = (C[i][j] == 0);
        }
    }

    S[0][0] = D[0][0];
    for (int i = 1; i < MAXN; i++) {
        S[i][0] = D[i][0] + S[i-1][0];
        S[0][i] = D[0][i] + S[0][i-1];
    }

    for (int i = 1; i < MAXN; i++) {
        for (int j = 1; j < MAXN; j++) {
            S[i][j] = D[i][j] + S[i-1][j] + S[i][j-1] - S[i-1][j-1];
        }
    }
}

int main() {
    scanf("%d%d", &T, &K);
    build();
    while (T--) {
        scanf("%d%d", &N, &M);
        printf("%d\n", S[N][M]);
    }

    return 0;
}
