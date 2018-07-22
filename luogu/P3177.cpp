// https://www.luogu.org/problemnew/show/P3177
// [HAOI2015]树上染色

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
        int wt;
    };

    vector<int> head;
    int eidx;
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

const int MAXN = 2010;
int N, K;
int sz[MAXN];
int64_t dp[MAXN][MAXN];

int64_t calc(int s, int j, int wt) {
    int64_t b1 = K - j, w1 = N-K-(s-j);
    int64_t b2 = j, w2 = s-j;
    return (b1*b2 + w1*w2) * wt;
}

int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

void combine(int u, int v, int curr_sz) {
    for (int i = min(K, curr_sz+sz[v]); i >= 0; i--) {
        for (int j = max3(0, sz[v]-(N-K), i-curr_sz); j <= min(sz[v], i); j++) {
            int k = i - j;
            if (dp[u][k] >= 0 && dp[v][j] >= 0) {
                dp[u][i] = max(dp[u][i], dp[u][k] + dp[v][j]);
            }
        }
    }
}

void dfs(const Graph &g, int u, int fa, int w) {
    dp[u][0] = 0;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            dfs(g, v, u, g.E[eidx].wt);
            combine(u, v, sz[u]);
            sz[u] += sz[v];
        }
    }
    sz[u]++;
    for (int i = min(sz[u], K); i >= max(0, sz[u]-(N-K)); i--) {
        int64_t t = calc(sz[u], i, w);
        if (dp[u][i] >= 0) dp[u][i] += t;
        if (i > 0 && dp[u][i-1] >= 0) dp[u][i] = max(dp[u][i], dp[u][i-1] + t);
    }
}

int main() {
    memset(dp, -1, sizeof(dp));
    scanf("%d%d", &N, &K);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g.addEdge(u, v, w);
        g.addEdge(v, u, w);
    }
    dfs(g, 0, 0, 0);
    printf("%lld\n", dp[0][K]);
    return 0;
}
