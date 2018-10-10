// https://www.luogu.org/problemnew/show/P3047
// [USACO12FEB]附近的牛Nearby Cows

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

const int MAXN = 100010;
int N, K;
int cnt[MAXN][21];
int C[MAXN];
int ans[MAXN][21];

void dfs1(const Graph &g, int u, int f) {
    cnt[u][0] = C[u];
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != f) {
            dfs1(g, v, u);
            for (int k = 1; k <= K; k++) {
                cnt[u][k] += cnt[v][k-1];
            }
        }
    }
}

void dfs2(const Graph &g, int u, int f) {
    for (int i = 0; i <= K; i++) {
        ans[u][i] = cnt[u][i];
    }
    if (f >= 0) {
        ans[u][1] += cnt[f][0];
        for (int k = 2; k <= K; k++) {
            ans[u][k] += ans[f][k-1] - cnt[u][k-2];
        }
    }
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != f) {
            dfs2(g, v, u);
        }
    }
}

int main() {
    scanf("%d%d", &N, &K);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }
    dfs1(g, 0, -1);
    dfs2(g, 0, -1);
    for (int i = 0; i < N; i++) {
        int tot = 0;
        for (int k = 0; k <= K; k++) {
            tot += ans[i][k];
        }
        printf("%d\n", tot);
    }
    return 0;
}
