// https://www.luogu.org/problem/show?pid=2327
// [SCOI2005] 扫雷

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;
int dp[MAXN][4];
int A[MAXN];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    if (A[1] == 2) {
        dp[1][1] = 1;
    } else if (A[1] == 1) {
        dp[1][0] = dp[1][1] = 1;
    } else if (A[1] == 0) {
        dp[1][0] = 1;
    } else {
        printf("0\n");
        return 0;
    }

    for (int i = 2; i <= N; i++) {
        for (int m = 0; m < 4; m++) {
            if (dp[i-1][m] == 0) continue;
            if (((m>>1)&1) + (m&1) == A[i-1] &&
                ((m&1) == A[i] || (m&1) == A[i]-1)) {
                dp[i][(m&1)<<1] += dp[i-1][m];
            }
            if (((m>>1)&1) + (m&1) == A[i-1] - 1 &&
                ((m&1) +1 == A[i] || (m&1) + 2 == A[i])) {
                dp[i][((m&1)<<1)|1] += dp[i-1][m];
            }
        }
    }
    int ans = 0;
    for (int m = 0; m < 4; m++) {
        if (((m>>1)&1) + (m&1) == A[N]) {
            ans += dp[N][m];
        }
    }
    printf("%d\n", ans);
    return 0;
}
