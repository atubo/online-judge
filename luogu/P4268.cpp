// https://www.luogu.org/problemnew/show/P4268
// [USACO18FEB]Directory Traversal

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

const int MAXN = 100010;
int S[MAXN];
int64_t D[MAXN];
int64_t ans;

struct Node {
    int len;
    bool isFile;
} nodes[MAXN];

int N;

void build(Graph &g) {
    for (int u = 0; u < N; u++) {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            g.E[eidx].wt = nodes[v].len + (!nodes[v].isFile);
        }
    }
}

void dfs1(const Graph &g, int u) {
    S[u] = nodes[u].isFile;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        dfs1(g, v);
        S[u] += S[v];
        D[u] += D[v] + 1LL*S[v]*w;
    }
}

void dfs2(const Graph &g, int u, int fa, int w) {
    if (fa != -1) {
        D[u] = D[fa] - 1LL*w*S[u] + 3LL*(S[0]-S[u]);
        ans = min(ans, D[u]);
    }
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int wt = g.E[eidx].wt;
        dfs2(g, v, u, wt);
    }
}

int main() {
    scanf("%d", &N);
    Graph g(N, N-1);

    char name[20];
    for (int i = 0; i < N; i++) {
        scanf("%s", name);
        int len = strlen(name);
        int m;
        scanf("%d", &m);
        nodes[i] = {len, m==0};
        for (int j = 0; j < m; j++) {
            int u;
            scanf("%d", &u);
            u--;
            g.addEdge(i, u, 0);
        }
    }

    build(g);

    dfs1(g, 0);

    ans = D[0];
    dfs2(g, 0, -1, 0);
    printf("%ld\n", ans);

    return 0;
}
