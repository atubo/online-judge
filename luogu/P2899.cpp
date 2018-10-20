// https://www.luogu.org/problemnew/show/P2899
// [USACO08JAN]手机网络Cell Phone Network

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

const int MAXN = 10010;
int N;
bool covered[MAXN];
int depth[MAXN], fa[MAXN];

void dfs(const Graph &g, int u, int f, int d) {
    fa[u] = f;
    depth[u] = d;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != f) {
            dfs(g, v, u, d+1);
        }
    }
}

struct Cmp {
    bool operator()(int u, int v) {
        return depth[u] < depth[v];
    }
};

void cover(const Graph &g, int u) {
    covered[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        covered[v] = true;
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
    dfs(g, 0, -1, 0);
    vector<int> x;
    priority_queue<int, vector<int>, Cmp> pq;
    for (int i = 0; i < N; i++) {
        pq.push(i);
    }

    int ans = 0;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        if (covered[u]) continue;
        ans++;
        cover(g, fa[u] == -1 ? u : fa[u]);
    }
    printf("%d", ans);
    return 0;
}
