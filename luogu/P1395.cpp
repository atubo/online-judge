// https://www.luogu.org/problemnew/show/P1395
// 会议

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

const int MAXN = 50010;
int N;
int D1[MAXN], D2[MAXN], S[MAXN];
int ans, node;

void dfs1(const Graph &g, int u, int fa) {
    S[u] = 1;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            dfs1(g, v, u);
            S[u] += S[v];
            D1[u] += D1[v];
        }
    }
    D1[u] += S[u]-1;
}

void dfs2(const Graph &g, int u, int fa) {
    if (fa != -1) {
        if (2*S[u] < N) return;
        D2[u] = D2[fa] + N - 2*S[u];
        if (D2[u] < ans || (D2[u] == ans && u < node)) {
            ans = D2[u];
            node = u;
        }
    }

    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            dfs2(g, v, u);
        }
    }
}

int main() {
    scanf("%d", &N);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
        g.addEdge(b, a);
    }
    dfs1(g, 0, -1);
    ans = D2[0] = D1[0], node = 0;
    dfs2(g, 0, -1);
    printf("%d %d\n", node+1, ans);
    return 0;
}
