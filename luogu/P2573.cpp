// https://www.luogu.org/problemnew/show/P2573
// [SCOI2012]滑雪

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

const int MAXN = 1e5+10;
const int MAXM = 1e6+10;
int H[MAXN];
struct Edge {
    int u, v, w;
    bool operator < (const Edge &other) const {
        if (H[v] != H[other.v]) return H[v] > H[other.v];
        if (w < other.w) return true;
        if (w > other.w) return false;
        if (u < other.u) return true;
        if (u > other.u) return false;
        return v < other.v;
    }
};

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
        size[k] = 1;
    }

    int link(int u, int v) {
        if (u == v) return u;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
            return u;
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            return v;
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);

        reset();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

int N, M;
bool vis[MAXN];
int ne;
Edge edges[MAXM*2];

void dfs(const Graph &g, int u) {
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        edges[ne++] = {u, v, w};
        if (!vis[v]) {
            dfs(g, v);
        }
    }
}

int64_t kruskal(const Graph &g) {
    UnionFind uf(N);
    int64_t ans = 0;
    for (int i = 0; i < ne; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (uf.find(u) == uf.find(v)) continue;
        ans += w;
        uf.join(u, v);
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &H[i]);
    }
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        u--; v--;
        if (H[u] >= H[v]) g.addEdge(u, v, k);
        if (H[v] >= H[u]) g.addEdge(v, u, k);
    }
    dfs(g, 0);
    sort(edges, edges+ne);
    int ans1 = 0;
    for (int i = 0; i < N; i++) ans1 += vis[i];
    int64_t ans2 = kruskal(g);
    printf("%d %ld", ans1, ans2);
    return 0;
}
