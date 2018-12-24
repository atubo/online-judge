// https://www.luogu.org/problemnew/show/P3959
// 宝藏

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
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

const int MAXN = 12;
const int64_t INF = 1e16;
int N, M;
int64_t dp[MAXN][MAXN][4096];

int64_t solve(const Graph &g, int l, int r, int s) {
    assert(((s >> r) & 1) == 0);
    if (dp[l][r][s] != -1) return dp[l][r][s];
    int64_t &ret = dp[l][r][s] = INF;
    if (s == 0) return ret = 0;
    for (int s1 = (s-1) & s; s1; s1 = (s1-1) & s) {
        int64_t x1 = solve(g, l, r, s1);
        int64_t x2 = solve(g, l, r, s-s1);
        if (x1 != INF && x2 != INF) {
            ret = min(ret, x1 + x2);
        }
    }
    for (int eidx = g.head[r]; ~eidx; eidx = g.E[eidx].next) {
        int t = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (((s>>t) & 1) == 0) continue;
        int64_t x = solve(g, l+1, t, s-(1<<t));
        if (x != INF) {
            ret = min(ret, x + int64_t(1)*(l+1)*w);
        }
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g.addEdge(u, v, w);
        g.addEdge(v, u, w);
    }
    int64_t ans = INF;
    for (int i = 0; i < N; i++) {
        ans = min(ans, solve(g, 0, i, (1<<N)-1-(1<<i)));
    }
    printf("%ld", ans);
    return 0;
}
