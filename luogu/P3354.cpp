// https://www.luogu.org/problemnew/show/P3354
// 河流

#include <bits/stdc++.h>
using namespace std;
const int inf = 2000000005;
const int MAXN = 110;

struct Node {
    int lc, rc, w, d;
} tree[MAXN];

int fa[MAXN], H[MAXN], dist[MAXN];
bool vis[MAXN];
int64_t dp[MAXN][MAXN][55];

int N, K;
int cnt;

void dfs(int s, int deep) {
    H[++cnt] = s;
    vis[s] = true;
    dist[s] = deep;
    for (int i = tree[s].lc; i; i = tree[i].rc) {
        if (!vis[i]) dfs(i, deep + tree[i].d);
    }
}

int main() {
    scanf("%d%d", &N, &K);
    memset(fa, -1, sizeof(fa));
    for (int i = 1; i <= N; i++) {
        int v;
        scanf("%d%d%d", &tree[i].w, &v, &tree[i].d);
        fa[i] = v;
        tree[i].rc = tree[v].lc;
        tree[v].lc = i;
    }
    dfs(0, 0);
    memset(dp, inf, sizeof(dp));
    memset(dp[0], 0, sizeof(dp[0]));

    for (int i = N+1; i >= 2; i--) {
        int now = H[i];
        int lson = tree[now].lc, rson = tree[now].rc;
        for (int j = fa[now]; j != -1; j = fa[j]) {
            for (int k = 0; k <= K; k++) {
                for (int l = 0; l <= k; l++) {
                    if (dp[lson][j][l] != inf && dp[rson][j][k-l] != inf) {
                        int64_t add = (int64_t)tree[now].w * (dist[now]-dist[j]);
                        dp[now][j][k] = min(dp[now][j][k],
                                            dp[lson][j][l] + dp[rson][j][k-l] + add);
                    }
                }
                for (int l = 0; l < k; l++) {
                    if (dp[lson][now][l] != inf && dp[rson][j][k-l-1] != inf) {
                        dp[now][j][k] = min(dp[now][j][k],
                                            dp[lson][now][l] + dp[rson][j][k-l-1]);
                    }
                }
            }
        }
    }
    printf("%lld\n", dp[tree[0].lc][0][K]);

    return 0;
}
