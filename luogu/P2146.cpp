// https://www.luogu.org/problemnew/show/P2146
// [NOI2015]软件包管理器

#include <bits/stdc++.h>
using namespace std;

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

    // 1-indexed
    class SegmentTree {
        int N;
        int64_t *val, *lazy;

    public:
        SegmentTree(int N_): N(N_) {
            val = new int64_t[4*N]{};
            lazy = new int64_t[4*N]{};
        }

        ~SegmentTree() {
            delete[] val;
            delete[] lazy;
        }
        // add t to range [a, b]
        void update(int t, int a, int b) {
            update(1, t, 1, N, a, b);
        }

        // query range sum in [a, b]
        int64_t query(int a, int b) {
            return query(1, a, b, 1, N);
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
            if (lazy[k] == -1) return;
            if (l == r) return;
            lazy[2*k] = lazy[k];
            lazy[2*k+1] = lazy[k];
            int mid = (l + r) / 2;
            val[2*k] = (mid - l + 1) * lazy[k];
            val[2*k+1] = (r - mid) * lazy[k];
            lazy[k] = -1;
        }

        // query range sum in [a, b], current node is [L, R]
        int64_t query(int k, int a, int b, int L, int R) {
            if (!k) return 0;
            if (b < L || a > R) return 0;
            pushDown(k, L, R);
            if (a <= L && R <= b) return val[k];
            int64_t sum = 0;
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
    vector<int> fa;
    vector<int> top;
    vector<int> in;
    vector<int> out;
    int root;
    int Seg_size;

    HeavyLightDecomposition(int N_): N(N_), g(N_), st(N_) {
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        stIdx.resize(N, -1);
        fa.resize(N);
        top.resize(N);
        in.resize(N);
        out.resize(N);

        root = 0;
        Seg_size = 1;   // segment tree is 1-indexed
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

    int install(int u) {
        int exist = queryNode(0, u);
        int total = dep[u] + 1;
        int ret = total - exist;
        updateNode(0, u, 1);
        return ret;
    }

    int uninstall(int u) {
        int exist = st.query(in[u], out[u]);
        int ret = exist;
        st.update(0, in[u], out[u]);
        return ret;
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
        if (u == root) {
            stIdx[u] = Seg_size++;
        }
        in[u] = stIdx[u];

        if (heavy[u] != -1) {
            int t = heavy[u];
            int v = g.E[t].to;
            stIdx[v] = Seg_size++;
            top[v] = top[u];
            dfs2(v, u);
        }

        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v == f || eidx == heavy[u]) continue;
            stIdx[v] = Seg_size++;
            top[v] = v;
            dfs2(v, u);
        }
        out[u] = Seg_size-1;
    }

    void updateEdgeChain(int u, int anc, int val) {
        while (u != anc) {
            int fe = rev[u];
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
                u = g.E[fe].to;
            }
        }
    }

    int queryEdgeChain(int anc, int u) {
        int ret = 0;
        while (u != anc) {
            int fe = rev[u];
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

int N, Q;

int main() {
    scanf("%d", &N);
    HeavyLightDecomposition hld(N);
    for (int i = 1; i < N; i++) {
        int x;
        scanf("%d", &x);
        hld.addEdge(i, x);
    }
    hld.decompose();

    scanf("%d", &Q);
    char cmd[15];
    for (int i = 0; i < Q; i++) {
        int x;
        scanf("%s%d", cmd, &x);
        if (cmd[0] == 'i') {
            printf("%d\n", hld.install(x));
        } else {
            printf("%d\n", hld.uninstall(x));
        }
    }

    return 0;
}
