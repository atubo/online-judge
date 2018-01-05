// https://www.luogu.org/problemnew/show/3931
// SAC E#1 - 一道难题 Tree

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 1000;
public:
    struct Edge {
        int next, to, w;
    };

    vector<int> head;
    vector<Edge> E;
    int eidx;
    int N, M;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        E.resize(M);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].w = w;
        head[u] = eidx++;
    }
};

const int MAXN = 100010;
int N, R;
int cost[MAXN];

void dfs(const Graph &g, int u, int father) {
    bool isLeaf = true;
    for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != father) {
            isLeaf = false;
            break;
        }
    }
    if (isLeaf) {
        cost[u] = INT_MAX;
        return;
    }

    int c = 0;
    for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].w;
        if (v != father) {
            dfs(g, v, u);
            c += min(cost[v], w);
        }
    }
    cost[u] = c;
}

int main() {
    scanf("%d%d", &N, &R);
    R--;
    Graph g(N, 2*N-2);
    for (int i = 0; i < N-1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        g.addEdge(a, b, c);
        g.addEdge(b, a, c);
    }
    dfs(g, R, -1);
    printf("%d\n", cost[R]);

    return 0;
}
