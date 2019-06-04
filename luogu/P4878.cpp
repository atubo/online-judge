// https://www.luogu.org/problemnew/show/P4878
// [USACO05DEC] 布局

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

const int INF = 0x3F3F3F3F;
const int MAXN = 1010;
int N, ML, MD;
int D[MAXN];

bool bellman(const Graph &g) {
    for (int i = 1; i < N; i++) {
        D[i] = INF;
    }

    for (int i = 0; i < N-1; i++) {
        for (int u = 0; u < N; u++) {
            for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
                int v = g.E[eidx].to;
                int w = g.E[eidx].wt;
                D[v] = min(D[v], D[u] + w);
            }
        }
    }

    int ret = true;
    for (int u = 0; u < N; u++) {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            if (D[u] + w < D[v]) {
                ret = false;
                break;
            }
        }
    }
    return ret;
}

int main() {
    scanf("%d%d%d", &N, &ML, &MD);
    Graph g(N, ML+MD);
    for (int i = 0; i < ML; i++) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        a--; b--;
        g.addEdge(a, b, d);
    }
    for (int i = 0; i < MD; i++) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        a--; b--;
        g.addEdge(b, a, -d);
    }

    bool ok = bellman(g);
    if (!ok) {
        printf("-1\n");
        return 0;
    }

    printf("%d\n", D[N-1] == INF ? -2 : D[N-1]);

    return 0;
}
