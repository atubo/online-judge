// https://www.luogu.org/problemnew/show/P2986
// [USACO10MAR]伟大的奶牛聚集Great Cow Gat…

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
int C[MAXN];
int N;
int S[MAXN];
int64_t L[MAXN];
int64_t ans = INT_MAX;

void dfs1(const Graph &g, int u, int fa) {
    S[u] = C[u];
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa) {
            dfs1(g, v, u);
            S[u] += S[v];
            L[u] += (L[v] + 1LL*S[v]*w);
        }
    }
}

void dfs2(const Graph &g, int u, int fa) {
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa) {
            if (2*S[v] < S[0]) continue;
            L[v] = L[u] - (2LL*S[v]-S[0])*w;
            ans = min(ans, L[v]);
            dfs2(g, v, u);
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }

    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        g.addEdge(a, b, c);
        g.addEdge(b, a, c);
    }

    dfs1(g, 0, -1);
    ans = L[0];
    dfs2(g, 0, -1);
    printf("%ld\n", ans);

    return 0;
}
