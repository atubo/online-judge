// https://www.luogu.org/problemnew/show/1191
// 矩形

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;
int N;
int M[MAXN][MAXN];
int dp[2][MAXN][MAXN];
int len[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char line[MAXN];
        scanf("%s", line);
        for (int j = 0; j < N; j++) {
            M[i][j] = (line[j] == 'B');
        }
    }

    int ans = 0;

    for (int r = 0; r < N; r++) {
        int curr = r & 1;
        int prev = curr ^ 1;
        memset(dp[curr], 0, sizeof(dp[curr]));
        memset(len, 0, sizeof(len));
        if (!M[r][0]) {
            len[0] = 1;
            dp[curr][0][0] = dp[prev][0][0] + 1;
            ans += dp[curr][0][0];
        }
        for (int c = 1; c < N; c++) {
            if (!M[r][c]) {
                int L = len[c] = len[c-1]+1;
                for (int i = c-L+1; i <= c; i++) {
                    dp[curr][i][c] = dp[prev][i][c] + 1;
                    ans += dp[curr][i][c];
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
