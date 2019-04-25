// https://www.luogu.org/problemnew/show/P2700
// 逐个击破

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to, wt;
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
        E[eidx].wt = w;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

struct Edge2 {
    int v, w;
};

const int MAXN = 100010;
int N, K;
bool C[MAXN];
vector<vector<Edge2>> E(MAXN);
bool F[MAXN];
int64_t dp[MAXN][2];

void dfs1(const Graph &g, int u, int fa) {
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa) {
            dfs1(g, v, u);
            if (F[v]) E[u].push_back({v, w});
        }
    }
    F[u] = (C[u] || E[u].size() > 0);
}

int64_t dfs2(const Graph &g, int u, int fa, int ec) {
    if (dp[u][ec] >= 0) return dp[u][ec];
    int64_t &ret = dp[u][ec] = 0;
    int64_t mx = 0;
    for (const auto &e: E[u]) {
        int64_t cost0 = dfs2(g, e.v, u, 0);
        int64_t cost1 = dfs2(g, e.v, u, 1);
        int64_t cost = (C[e.v] ? cost0+e.w : min(cost0+e.w, cost1));
        ret += cost;
        mx = max(mx, cost - cost0);
    }
    if (!C[u] && !ec) ret -= mx;
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));

    scanf("%d%d", &N, &K);
    for (int i = 0; i < K; i++) {
        int u;
        scanf("%d", &u);
        C[u] = true;
    }
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g.addEdge(a, b, c);
        g.addEdge(b, a, c);
    }
    dfs1(g, 0, -1);
    dfs2(g, 0, -1, 0);
    printf("%ld", dp[0][0]);

    return 0;
}
