// https://www.luogu.org/problem/show?pid=1220
// 关路灯

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
int dp[MAXN][MAXN][MAXN];
int X[MAXN], P[MAXN];
int N, C;

int pwr(int p, int q) {
    return P[p] + P[N] - P[q-1];
}

int solve(int k, int p, int q) {
    if (dp[k][p][q] != -1) {
        return dp[k][p][q];
    }

    int power = pwr(p, q);
    int& ans = dp[k][p][q];
    if (p == 0 && q == N+1) {
        return ans = 0;
    }
    if (p == 0) {
        return ans = (X[q]-X[k])*power + solve(q, p, q+1);
    }
    if (q == N+1) {
        return ans = (X[k]-X[p])*power + solve(p, p-1, q);
    }
    return ans = min((X[q] - X[k]) * power + solve(q, p, q+1),
                     (X[k] - X[p]) * power + solve(p, p-1, q));
}

int main() {
    scanf("%d %d", &N, &C);
    for (int i = 1; i <= N; i++) {
        scanf("%d %d", &X[i], &P[i]);
        P[i] += P[i-1];
    }

    for (int i = 0; i <= N+1; i++) {
        for (int j = 0; j <= N+1; j++) {
            for (int k = 0; k <= N+1; k++) {
                dp[i][j][k] = -1;
            }
        }
    }

    int ans = solve(C, C-1, C+1);
    printf("%d\n", ans);
    return 0;
}
