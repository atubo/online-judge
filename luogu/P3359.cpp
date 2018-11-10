// https://www.luogu.org/problemnew/show/P3359
// 改造异或树

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

struct Conn {
    int a, b;
};

const int MAXN = 1e5+10;
int N;
int dist[MAXN];

void dfs(const Graph &g, int u, int f, int d) {
    dist[u] = d;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != f) {
            dfs(g, v, u, d^w);
        }
    }
}

int main() {
    using Map = map<int, int64_t>;
    scanf("%d", &N);
    Graph g(N, 2*(N-1));
    vector<Conn> conn;
    for (int i = 0; i < N-1; i++) {
        int a, b, z;
        scanf("%d%d%d", &a, &b, &z);
        a--; b--;
        g.addEdge(a, b, z);
        g.addEdge(b, a, z);
        conn.push_back({a, b});
    }
    dfs(g, 0, -1, 0);

    vector<int> cut;
    for (int i = 0; i < N-1; i++) {
        int x;
        scanf("%d", &x);
        cut.push_back(x-1);
    }

    UnionFind uf(N);
    vector<Map*> cnt(N);
    for (int i = 0; i < N; i++) {
        cnt[i] = new Map();
        (*cnt[i])[dist[i]] = 1;
    }

    vector<int64_t> ans(N);
    for (int i = N-2; i >= 0; i--) {
        ans[i] = ans[i+1];
        int eidx = cut[i];
        int a = conn[eidx].a, b = conn[eidx].b;
        int u = uf.find(a), v = uf.find(b);
        Map *ma = cnt[u], *mb = cnt[v];
        if (ma->size() < mb->size()) swap(ma, mb);
        for (auto it = mb->cbegin(); it != mb->cend(); ++it) {
            int x = it->first;
            ans[i] += ((*ma)[x]) * ((*mb)[x]);
            (*ma)[x] += (*mb)[x];
        }
        int w = uf.join(u, v);
        cnt[w] = ma;
    }
    for (int i = 0; i < N; i++) {
        printf("%ld\n", ans[i]);
    }
    return 0;
}
