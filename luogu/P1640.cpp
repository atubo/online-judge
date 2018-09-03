// https://www.luogu.org/problemnew/show/P1640
// [SCOI2010]连续攻击游戏

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

const int MAXN = 1000010;
int N;

bool vis[MAXN];
int deg[MAXN];


bool visit(const Graph &g, int u, int s) {
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (vis[v]) continue;
        deg[v]--;
        if (deg[v] == 0 && v < s) return false;
        if (deg[v] == 1 && v < s) return visit(g, v, s);
    }
    return true;
}


int solve(const Graph &g) {
    for (int i = 1; i <= N; i++) {
        if (deg[i] == 0) return i-1;
        if (deg[i] == 1) {
            bool ok = visit(g, i, i);
            if (!ok) return i-1;
        }
    }
    return N;
}

int main() {
    scanf("%d", &N);
    Graph g(N+1, 2*N);
    for (int i = 0; i < N; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a <= N && b <= N) {
            g.addEdge(a, b);
            g.addEdge(b, a);
        }
        if (a <= N) deg[a]++;
        if (b <= N) deg[b]++;
    }
    printf("%d\n", solve(g));
    return 0;
}
