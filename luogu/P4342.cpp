// https://www.luogu.org/problemnew/show/P4342
// [IOI1998]Polygon

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 60;
int N;
int dp1[MAXN*2][MAXN], dp2[MAXN*2][MAXN];
int A[MAXN*2], op[MAXN*2];

void calc(int a, int b, int c, int d, int o, int &d1, int &d2) {
    if (o == 0) {
        d1 = min(d1, min(a, b) + min(c, d));
        d2 = max(d2, max(a, b) + max(c, d));
    } else {
        d1 = min(d1, min(min(a*c, a*d), min(b*c, b*d)));
        d2 = max(d2, max(max(a*c, a*d), max(b*c, b*d)));
    }
}

int main() {
    scanf("%d", &N);
    char cmd[10];
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%s%d", cmd, &x);
        if (i == 0) op[N-1] = (cmd[0] == 'x');
        else op[i-1] = op[i-1+N] = (cmd[0] == 'x');
        A[i] = A[i+N] = x;
    }

    for (int i = 0; i < 2*N-1; i++) {
        dp1[i][0] = dp2[i][0] = A[i];
    }

    for (int k = 1; k <= N-1; k++) {
        for (int i = 0; i <= 2*N-2-k; i++) {
            dp1[i][k] = INT_MAX;
            dp2[i][k] = INT_MIN;
            for (int j = i; j <= i+k-1; j++) {
                calc(dp1[i][j-i], dp2[i][j-i],
                     dp1[j+1][i+k-j-1], dp2[j+1][i+k-j-1],
                     op[j], dp1[i][k], dp2[i][k]);
            }
        }
    }

    int ans = INT_MIN;
    for (int i = 0; i < N; i++) {
        ans = max(ans, dp2[i][N-1]);
    }
    printf("%d\n", ans);
    for (int i = 0; i < N; i++) {
        if (dp2[i][N-1] == ans) printf("%d ", i+1);
    }

    return 0;
}
