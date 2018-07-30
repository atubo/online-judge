// https://www.luogu.org/problemnew/show/P3761
// [TJOI2017]城市

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

int maxd, maxu, maxv, minr;

void dfs1(const Graph &g, int u, int fa, int d) {
    if (d > maxd) {
        maxd = d;
        maxu = u;
    }
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa) {
            dfs1(g, v, u, d+w);
        }
    }
}

void dfs2(const Graph &g, int u, int fa, int t, int d) {
    if (d > maxd) {
        maxd = d;
        maxv = u;
    }
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa && v != t) {
            dfs2(g, v, u, t, d+w);
        }
    }
}

bool dfs3(const Graph &g, int u, int fa, int t, int d) {
    if (u == maxv) {
        minr = maxd;
        return true;
    }
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa && v != t) {
            if (dfs3(g, v, u, t, d+w)) {
                minr = min(minr, max(maxd-d, d));
                return true;
            }
        }
    }
    return false;
}

void solveTree(const Graph &g, int s, int t) {
    // given a tree, find l1 and l2
    // first dfs
    maxd = -1, maxu = -1;
    dfs1(g, s, t, 0);
    // second dfs to find v
    maxd = -1, maxv = -1;
    dfs2(g, maxu, -1, t, 0);

    // third dfs to find minr;
    minr = INT_MAX;
    dfs3(g, maxu, -1, t, 0);
}

int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

int N;

int main() {
    scanf("%d", &N);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        u--; v--;
        g.addEdge(u, v, d);
        g.addEdge(v, u, d);
    }
    int ans = INT_MAX;
    for (int eidx = 0; eidx < 2*(N-1); eidx+=2) {
        int u = g.E[eidx].to;
        int v = g.E[eidx^1].to;
        int w = g.E[eidx].wt;
        solveTree(g, u, v);
        int l1 = minr, l2 = maxd-l1;
        if (l1 + l2 > ans || l1 + w > ans) continue;
        solveTree(g, v, u);
        int l3 = minr, l4 = maxd-l3;
        ans = min(ans, max3(l1+l2, l3+l4, l1+l3+w));
    }
    printf("%d\n", ans);
    return 0;
}
