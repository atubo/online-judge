// https://www.luogu.org/problemnew/show/P2015
// 二叉苹果树

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
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
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

const int MAXN = 110;
int N, Q;
int A[MAXN], depth[MAXN], L[MAXN], R[MAXN];
int dp[MAXN][MAXN];
struct Edge {
    int u, v, w;
} edge[MAXN];

void dfs(const Graph &g, int u, int fa, int d) {
    depth[u] = d;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            if (L[u] == -1) L[u] = v;
            else R[u] = v;
            dfs(g, v, u, d+1);
        }
    }
}

#if 1
int solve(int u, int q) {
    assert(u >= 0 && q >= 0);
    if (dp[u][q] >= 0) return dp[u][q];
    int &ret = dp[u][q];
    if (q == 0 || L[u] == -1) return ret = A[u];
    ret = A[u] + max(solve(L[u], q-1), solve(R[u], q-1));
    for (int y = 0; y <= q-2; y++) {
        ret = max(ret, A[u] + solve(L[u], y) + solve(R[u], q-2-y));
    }
    return ret;
}
#endif


int main() {
    memset(dp, -1, sizeof(dp));
    memset(L, -1, sizeof(L));
    memset(R, -1, sizeof(R));
    scanf("%d%d", &N, &Q);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        edge[i] = {u, v, w};
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    dfs(g, 0, 0, 0);
    for (int i = 0;i < N-1; i++) {
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        if (depth[u] < depth[v]) A[v] = w;
        else A[u] = w;
    }
    printf("%d", solve(0, Q));

    return 0;
}
