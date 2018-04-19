// https://www.luogu.org/problemnew/show/P3942
// 将军令

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 1000;
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    int eidx;
    int N;

    Edge *E;

    Graph(int N_, int M):N(N_) {
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

using Pii = pair<int, int>;

const int MAXN = 100010;
int N, K, T;
int father[MAXN], depth[MAXN];
bool covered[MAXN];

void dfs1(const Graph &g, int u, int fa, int dep) {
    father[u] = fa;
    depth[u] = dep;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v == fa) continue;
        dfs1(g, v, u, dep+1);
    }
}

void dfs2(const Graph &g, int u, int from, int d) {
    covered[u] = true;
    if (d > 0) {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v == from) continue;
            dfs2(g, v, u, d-1);
        }
    }
}

void cover(const Graph &g, int u) {
    for (int i = 0; i < K; i++) {
        if (father[u] == -1) break;
        u = father[u];
    }
    dfs2(g, u, u, K);
}

int main() {
    scanf("%d%d%d", &N, &K, &T);
    Graph g(N, 2*N);
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }
    dfs1(g, 0, -1, 0);
    priority_queue<Pii> pq;
    for (int i = 0; i < N; i++) {
        pq.push(make_pair(depth[i], i));
    }
    int ret = 0;
    while (!pq.empty()) {
        Pii pii = pq.top();
        pq.pop();
        int u = pii.second;
        if (!covered[u]) {
            cover(g, u);
            ret++;
        }
    }

    printf("%d", ret);

    return 0;
}
