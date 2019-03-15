// https://www.luogu.org/problemnew/show/P1140
// 相似基因

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int N, M;
char A[MAXN], B[MAXN];
int dp[MAXN][MAXN];

int decode(char c) {
    if (c == 'A') return 0;
    else if (c == 'C') return 1;
    else if (c == 'G') return 2;
    else return 3;
}

const int S[5][5] = {
    5, -1, -2, -1, -3,
    -1, 5, -3, -2, -4,
    -2, -3, 5, -2, -2,
    -1, -2, -2, 5, -1,
    -3, -4, -2, -1, -100000000};

int main() {
    scanf("%d", &N);
    scanf("%s", A+1);
    scanf("%d", &M);
    scanf("%s", B+1);
    for (int i = 1; i <= N; i++) {
        dp[i][0] = dp[i-1][0] + S[decode(A[i])][4];
    }
    for (int i = 1; i <= M; i++) {
        dp[0][i] = dp[0][i-1] + S[4][decode(B[i])];
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int c1 = decode(A[i]);
            int c2 = decode(B[j]);
            dp[i][j] = dp[i-1][j-1] + S[c1][c2];
            dp[i][j] = max(dp[i][j], dp[i-1][j] + S[c1][4]);
            dp[i][j] = max(dp[i][j], dp[i][j-1] + S[4][c2]);
        }
    }
    printf("%d\n", dp[N][M]);
    return 0;
}
