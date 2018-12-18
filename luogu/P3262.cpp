// https://www.luogu.org/problemnew/show/P3262
// [JLOI2015]战争调度

#include <bits/stdc++.h>
using namespace std;

int N, M;
int W[1024][10], F[1024][10];
int dp[1024][1024];
bool path[10];

void dfs(int u, int d) {
    if (d == N) {
        int tw = 0, tf = 0;
        for (int i = 1; i < N; i++) {
            if (path[i]) tw += W[u][i];
            else         tf += F[u][i];
        }
        dp[u][0] = tf;
        dp[u][1] = tw;
        return;
    }

    path[d] = 0;
    dfs(2*u, d+1); dfs(2*u+1, d+1);
    for (int c = 0; c <= (1<<(N-d)); c++) {
        dp[u][c] = 0;
        for (int c1 = 0; c1 <= c; c1++) {
            dp[u][c] = max(dp[u][c], dp[2*u][c1] + dp[2*u+1][c-c1]);
        }
    }
    path[d] = 1;
    dfs(2*u, d+1); dfs(2*u+1, d+1);
    for (int c = 0; c <= (1<<(N-d)); c++) {
        for (int c1 = 0; c1 <= c; c1++) {
            dp[u][c] = max(dp[u][c], dp[2*u][c1]+dp[2*u+1][c-c1]);
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1<<(N-1); i < 1<<N; i++) {
        for (int j = 1; j <= N-1; j++) {
            scanf("%d", &W[i][N-j]);
        }
    }
    for (int i = 1<<(N-1); i < 1<<N; i++) {
        for (int j = 1; j <= N-1; j++) {
            scanf("%d", &F[i][N-j]);
        }
    }
    dfs(1, 1);
    int ans = 0;
    for (int i = 0; i <= M; i++) {
        ans = max(ans, dp[1][i]);
    }
    printf("%d\n", ans);
    return 0;
}
