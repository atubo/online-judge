// https://www.luogu.org/problemnew/show/P3629
// [APIO2010]巡逻

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
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = 1;
        head[u] = eidx++;
    }
};

int N, K;

void dfs(const Graph &g, int u, int fa, int d, int &dmax, int &r) {
    if (d > dmax) {
        dmax = d;
        r = u;
    }
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) dfs(g, v, u, d+1, dmax, r);
    }
}

bool dfs2(Graph &g, int u, int fa, int t) {
    if (u == t) return true;
    bool ret = false;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            bool ok = dfs2(g, v, u, t);
            if (ok) {
                g.E[eidx].wt = g.E[eidx^1].wt = -1;
                ret = true;
            }
        }
    }
    return ret;
}

int dfs3(const Graph &g, int u, int fa, int &dmax2) {
    vector<int> d;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa) {
            d.push_back(max(0, w + dfs3(g, v, u, dmax2)));
        }
    }
    if (d.empty()) return 0;
    sort(d.begin(), d.end(), greater<int>());

    if (d.size() == 1) dmax2 = max(dmax2, d[0]);
    else dmax2 = max(dmax2, d[0]+d[1]);
    return d[0];
}

int main() {
    scanf("%d%d", &N, &K);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
        g.addEdge(b, a);
    }
    int dmax1 = 0, u = 0, v = 0;
    dfs(g, 0, 0, 0, dmax1, u);
    dmax1 = 0;
    dfs(g, u, u, 0, dmax1, v);

    if (K == 1) {
        printf("%d\n", 2*N-dmax1-1);
    } else {
        dfs2(g, u, u, v);

        int dmax2 = 0;
        dfs3(g, 0, 0, dmax2);
        printf("%d\n", 2*N-dmax1-dmax2);
    }

    return 0;
}
