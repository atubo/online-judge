//https://www.luogu.org/problemnew/show/P4322
// [JSOI2016]最佳团体

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2510;
int K, N;
int S[MAXN], P[MAXN], R[MAXN];
double A[MAXN];
double dp[MAXN][MAXN];
int dfn[MAXN], nex[MAXN];
int TCURR;

void dfs(int u, const vector<vector<int>> &adj) {
    dfn[u] = TCURR++;
    for (int v: adj[u]) {
        dfs(v, adj);
    }
    nex[dfn[u]] = TCURR;
}

#define MAX(a, b) a=a>b?a:b

bool check(double mid) {
    for (int i = 1; i <= N; i++) {
        A[dfn[i]] = P[i] - mid*S[i];
    }

    for (int i = 0; i <= N+1; i++) {
        for (int j = 0; j <= K+1; j++) {
            dp[i][j] = -1e9;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K+1; j++) {
            if (dp[i][j] != -1e9) {
                MAX(dp[i+1][j+1], (dp[i][j]+A[i]));
                MAX(dp[nex[i]][j], dp[i][j]);
            }
        }
    }

    return dp[N+1][K+1] >= 0;
}

int main() {
    scanf("%d%d", &K, &N);
    vector<vector<int>> adj(N+1);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d%d", &S[i], &P[i], &R[i]);
        adj[R[i]].push_back(i);
    }
    dfs(0, adj);
    const double EPS = 1e-4;
    double lo = 0, hi = 1e4+1;
    while (lo < hi - EPS) {
        double mid = (lo + hi) / 2;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    printf("%.3f\n", lo);
    return 0;
}
