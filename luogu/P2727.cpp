// https://www.luogu.org/problemnew/show/P2727
// 01串 Stringsobits

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 33;
int N, L;
int64_t X;
int dp[MAXN][MAXN];
int64_t ps[MAXN][MAXN];

int main() {
    scanf("%d%d%ld", &N, &L, &X);
    dp[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= L; j++) {
            dp[i][j] = dp[i-1][j];
            if (j > 0) dp[i][j] += dp[i-1][j-1];
        }
    }
    for (int i = 0; i <= N; i++) {
        ps[i][0] = dp[i][0];
        for (int j = 1; j <= L; j++) {
            ps[i][j] = ps[i][j-1] + dp[i][j];
        }
    }
    if (X > ps[N][L]) {
        printf("-1\n");
        return 0;
    }
    int ans = 0, l = L;
    int64_t x = X;
    for (int i = N-1; i >= 0; i--) {
        if (x > ps[i][l]) {
            x -= ps[i][l];
            l--;
            ans |= (1<<i);
        }
    }
    for (int i = N-1; i >= 0; i--) {
        char c = '0' + ((ans >> i) & 1);
        printf("%c", c);
    }
    printf("\n");
    return 0;
}
