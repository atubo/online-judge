// https://www.luogu.org/problemnew/show/P2294
// [HNOI2005]狡猾的商人

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

const int MAXN = 110;
int W;
int N, M;
bool vis[MAXN];
int dist[MAXN];

bool dfs(const Graph &g, int u, int d) {
    vis[u] = true;
    dist[u] = d;

    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (vis[v] && d + w != dist[v]) return false;
        if (!vis[v]) {
            if (!dfs(g, v, d+w)) return false;
        }
    }
    return true;
}

bool solve() {
    scanf("%d%d", &N, &M);
    memset(vis, 0, (N+1)*sizeof(bool));
    memset(dist, 0, (N+1)*sizeof(int));
    Graph g(N+1, 2*M);
    for (int i = 0; i < M; i++) {
        int s, t, v;
        scanf("%d%d%d", &s, &t, &v);
        g.addEdge(t, s-1, v);
        g.addEdge(s-1, t, -v);
    }
    for (int u = 0; u <= N; u++) {
        if (!vis[u]) {
            bool ret = dfs(g, u, 0);
            if (!ret) return false;
        }
    }
    return true;
}


int main() {
    scanf("%d", &W);
    while (W--) {
        bool ret = solve();
        printf(ret ? "true\n" : "false\n");
    }
    return 0;
}
