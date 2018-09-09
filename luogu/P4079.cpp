// https://www.luogu.org/problemnew/show/P4079
// [SDOI2016]齿轮

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
        double wt;
        int sgn;
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
    void addEdge(int u, int v, double l, int s) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = l;
        E[eidx].sgn = s;
        head[u] = eidx++;
    }
};

const int MAXN = 1010;
int T, N, M;
double pot[MAXN];
int sgn[MAXN];
bool vis[MAXN];

void cleanup() {
    memset(vis, 0, N*sizeof(bool));
    memset(sgn, 0, N*sizeof(int));
    memset(pot, 0, N*sizeof(double));
}

bool dfs(int u, double d, int s, const Graph &g) {
    vis[u] = true;
    pot[u] = d;
    sgn[u] = s;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        double w = g.E[eidx].wt;
        int sv = g.E[eidx].sgn;
        if (vis[v]) {
            if (sgn[v] != sgn[u] * sv ||
                fabs(pot[v] - pot[u] - w) > 1e-6) {
                return false;
            }
        } else {
            if (!dfs(v, d+w, s*sv, g)) return false;
        }
    }

    return true;
}

bool solve() {
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int u, v, x, y;
        scanf("%d%d%d%d", &u, &v, &x, &y);
        u--; v--;
        int s = (y > 0 ? 1 : -1);
        double lg = log(1.0 * x / abs(y));
        g.addEdge(u, v, -lg, s);
        g.addEdge(v, u, lg, s);
    }

    for (int u = 0; u < N; u++) {
        if (!vis[u]) {
            if (!dfs(u, 0, 1, g)) {
                cleanup();
                return false;
            }
        }
    }
    cleanup();
    return true;
}

int main() {
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: ", i);
        bool ok = solve();
        if (ok) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
