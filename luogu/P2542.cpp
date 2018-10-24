// https://www.luogu.org/problemnew/show/P2542
// [AHOI2005]航线规划

#include <bits/stdc++.h>
using namespace std;

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

class HeavyLightDecomposition {
private:
    // Note graph node is 0-indexed
    class Graph {
    public:
        struct Edge {
            int next, to;
        };

        vector<int> head;
        int eidx;
        int N;

        Edge *E;

        Graph(int N_):N(N_) {
            head.resize(N);
            eidx = 0;

            for (int i = 0; i < N; i++) {
                head[i] = -1;
            }

            // since this should be a tree
            E = new Edge[2*N-2]{};
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

    // 0-indexed
    class SegmentTree {
        int N;
        int *val, *lazy;

    public:
        SegmentTree(int N_): N(N_) {
            val = new int[4*N]{};
            lazy = new int[4*N]{};
            memset(lazy, -1, 4*N*sizeof(int));
        }

        ~SegmentTree() {
            delete[] val;
            delete[] lazy;
        }
        // add t to range [a, b]
        void update(int t, int a, int b) {
            update(1, t, 0, N-1, a, b);
        }

        // query range sum in [a, b]
        int query(int a, int b) {
            return query(1, a, b, 0, N-1);
        }

    private:
        // add t to range [a, b], current node range is [l, r]
        void update(int k, int t, int l, int r, int a, int b) {
            if (a > b) return;
            pushDown(k, l, r);
            if (a <= l && r <= b) {
                val[k] = t * (r-l+1);
                lazy[k] = t;
                return;
            }
            if (l == r) return;
            int mid = (l + r) / 2;
            if (a <= mid) update(2*k,   t, l, mid, a, b);
            if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
            val[k] = val[2*k] + val[2*k+1];
        }

        void pushDown(int k, int l, int r) {
            if (lazy[k] == -1 || l == r) return;
            lazy[2*k] = lazy[k];
            lazy[2*k+1] = lazy[k];
            int mid = (l + r) / 2;
            val[2*k] = (mid - l + 1) * lazy[k];
            val[2*k+1] = (r - mid) * lazy[k];
            lazy[k] = -1;
        }

        // query range sum in [a, b], current node is [L, R]
        int query(int k, int a, int b, int L, int R) {
            if (!k) return 0;
            if (b < L || a > R) return 0;
            pushDown(k, L, R);
            if (a <= L && R <= b) return val[k];
            int sum = 0;
            int mid = (L + R) / 2;
            if (a <= mid) sum += query(2*k, a, b, L, mid);
            if (mid < b)  sum += query(2*k+1, a, b, mid+1, R);
            return sum;
        }
    };

public:
    const int N;
    Graph g;
    SegmentTree st;
    vector<int> size;
    vector<int> dep;
    vector<int> rev;    // node to father-edge
    vector<int> heavy;
    vector<int> stIdx;    // node to segment tree index
    vector<int> fa; // father along heavy chain, -1 is father-edge isn't heavy
    vector<int> top;
    int root;
    int Seg_size;

    HeavyLightDecomposition(int N_): N(N_), g(N_), st(N_) {
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        stIdx.resize(N, -1);
        fa.resize(N, -1);
        top.resize(N);

        root = 0;
        Seg_size = 0;   // segment tree is 1-indexed
    }

    void addEdge(int u, int v) {
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    void decompose() {
        dfs1(root, root);
        top[root] = root;
        dfs2(root, root);
    }

    void updateNode(int u, int v, int d) {
        updateEdge(u, v, d);
        int p = lca(u, v);
        int r = stIdx[p];
        st.update(d, r, r);
    }

    int queryNode(int u, int v) {
        int ret = queryEdge(u, v);
        int p = lca(u, v);
        int r = stIdx[p];
        ret += st.query(r, r);
        return ret;
    }

    void updateEdge(int u, int v, int d) {
        int p = lca(u, v);;
        updateEdgeChain(u, p, d);
        updateEdgeChain(v, p, d);
    }

    int queryEdge(int u, int v) {
        int ret = 0;
        int p = lca(u, v);
        ret += queryEdgeChain(p, u);
        ret += queryEdgeChain(p, v);
        return ret;
    }

private:
    void dfs1(int u, int f) {
        int mx = -1, e = -1;
        size[u] = 1;

        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v == f) continue;
            dep[v] = dep[u] + 1;
            rev[v] = eidx ^ 1;
            dfs1(v, u);
            size[u] += size[v];
            if (size[v] > mx) {
                mx = size[v];
                e = eidx;
            }
        }
        heavy[u] = e;
        if (e != -1) fa[g.E[e].to] = u;
    }

    void dfs2(int u, int f) {
        stIdx[u] = Seg_size++;

        if (heavy[u] != -1) {
            int t = heavy[u];
            int v = g.E[t].to;
            top[v] = top[u];
            dfs2(v, u);
        }

        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v == f || eidx == heavy[u]) continue;
            top[v] = v;
            dfs2(v, u);
        }
    }

    void updateEdgeChain(int u, int anc, int val) {
        while (u != anc) {
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                st.update(val, l, r);
                u = p;
            } else {
                int r = stIdx[u];
                st.update(val, r, r);
                int fe = rev[u];
                u = g.E[fe].to;
            }
        }
    }

    int queryEdgeChain(int anc, int u) {
        int ret = 0;
        while (u != anc) {
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                ret += st.query(l, r);
                u = p;
            } else {
                int r = stIdx[u];
                ret += st.query(r, r);
                int fe = rev[u];
                u = g.E[fe].to;
            }
        }
        return ret;
    }


    int lca(int u, int v) {
        while (true) {
            int a = top[u], b = top[v];
            if (a == b) return dep[u] < dep[v] ? u : v;
            else if (dep[a] >= dep[b]) u = g.E[rev[a]].to;
            else v = g.E[rev[b]].to;
        }
    }

    int heavyChild(int u) const {
        int e = heavy[u];
        int ret = 0;
        if (e != -1) {
            ret = g.E[e].to;
        }
        return ret;
    }
};
struct Query {
    int u, v, t;
};

struct Route {
    int u, v;
    bool operator < (const Route &other) const {
        if (u < other.u) return true;
        if (u > other.u) return false;
        return (v < other.v);
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    set<Route> routes;
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        if (u > v) swap(u, v);
        routes.insert({u, v});
    }

    vector<Query> queries;
    while (true) {
        int c, a, b;
        scanf("%d", &c);
        if (c == -1) break;
        scanf("%d%d", &a, &b);
        a--; b--;
        if (a > b) swap(a, b);
        queries.push_back({a, b, c});
        if (c == 0) {
            assert(routes.count({a, b}) > 0);
            routes.erase({a, b});
        }
    }

    int curr = N;
    UnionFind uf(N);
    HeavyLightDecomposition hld(2*N-1);
    vector<Route> conn;
    for (const auto r: routes) {
        int u = r.u, v = r.v;
        if (uf.find(u) != uf.find(v)) {
            hld.addEdge(u, curr);
            hld.addEdge(curr, v);
            curr++;
            uf.join(u, v);
        } else {
            conn.push_back(r);
        }
    }
    hld.decompose();

    for (int u = N; u < 2*N-1; u++) {
        hld.updateNode(u, u, 1);
    }

    for (const auto &r: conn) {
        hld.updateNode(r.u, r.v, 0);
    }

    vector<int> ans;
    for (int i = queries.size()-1; i >= 0; i--) {
        int u = queries[i].u, v = queries[i].v, t = queries[i].t;
        if (t == 0) {
            hld.updateNode(u, v, 0);
        } else {
            ans.push_back(hld.queryNode(u, v));
        }
    }

    for (int i = ans.size()-1; i >= 0; i--) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
