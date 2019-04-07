// https://www.luogu.org/problemnew/show/P2458
// [SDOI2006]保安站岗

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1510;
int N;
vector<vector<int>> C;
int cost[MAXN];
int dp[MAXN][2][2];
int father[MAXN];
int dp2[MAXN][2][MAXN];
const int INF = 2e7;

int solve(int u, int cf, int cu) {
    if (dp[u][cf][cu] != -1) return dp[u][cf][cu];
    int &ret = dp[u][cf][cu] = 0;
    const int m = C[u].size();
    if (cf == 0 && cu == 0) {
        for (int i = 1; i < m; i++) {
            int v = C[u][i];
            int c0 = solve(v, 0, 0);
            int c1 = solve(v, 0, 1);
            dp2[u][0][i] = dp2[u][0][i-1] + c0;
            dp2[u][1][i] = min(dp2[u][1][i-1] + c0,
                            min(dp2[u][1][i-1], dp2[u][0][i-1]) + c1);
        }
        ret = dp2[u][1][m-1];
    } else {
        if (cu) ret = cost[u];
        for (int i = 1; i < m; i++) {
            int v = C[u][i];
            int c0 = solve(v, cu, 0);
            int c1 = solve(v, cu, 1);
            ret += min(c0, c1);
        }
    }
    return ret;
}

int main() {
    memset(father, -1, sizeof(father));
    memset(dp, -1, sizeof(dp));
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        dp2[i][1][0] = INF;
    }
    C.resize(N);
    for (int i = 0; i < N; i++) {
        int u, k, m;
        scanf("%d%d%d", &u, &k, &m);
        u--;
        cost[u] = k;
        C[u].resize(m+1);
        for (int j = 1; j <= m; j++) {
            int v;
            scanf("%d", &v);
            v--;
            C[u][j] = v;
            father[v] = u;
        }
    }
    int root = -1;
    for (int i = 0; i < N; i++) {
        if (father[i] == -1) {
            root = i;
            break;
        }
    }

    int ans = min(solve(root, 0, 0), solve(root, 0, 1));
    printf("%d\n", ans);

    return 0;
}
