// https://www.luogu.org/problemnew/show/P3907
// 圈的异或

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

int N, M;
bool vis[60];
int dist[60];

bool dfs(const Graph &g, int u, int d) {
    vis[u] = true;
    dist[u] = d;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (!vis[v]) {
            int ok = dfs(g, v, d^w);
            if (!ok) return false;
        } else {
            if ((dist[u] ^ dist[v]) != w) return false;
        }
    }
    return true;
}

void solve() {
    memset(vis, 0, sizeof(vis));
    memset(dist, 0, sizeof(dist));
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        g.addEdge(a, b, c);
        g.addEdge(b, a, c);
    }
    bool ret = true;
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            bool ok = dfs(g, i, 0);
            if (!ok) {
                ret = false;
                break;
            }
        }
    }
    printf(ret ? "Yes\n" : "No\n");
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
