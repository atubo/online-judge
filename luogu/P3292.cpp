// https://www.luogu.org/problemnew/show/P3292
// [SCOI2016]幸运数字

#include <bits/stdc++.h>
using namespace std;

class XorLinearBasis {
public:
    int64_t *a;

    XorLinearBasis(int maxl=60): maxl_(maxl) {
        alloc();
    }

    XorLinearBasis(const XorLinearBasis &b) {
        maxl_ = b.maxl_;
        alloc();
        memcpy(a, b.a, maxl_*sizeof(int64_t));
    }

    XorLinearBasis& operator = (const XorLinearBasis &other) {
        dealloc();
        maxl_ = other.maxl_;
        alloc();
        memcpy(a, other.a, maxl_*sizeof(int64_t));
        return *this;
    }

    ~XorLinearBasis() {
        dealloc();
    }

    void insert(int64_t t) {
        for (int j = maxl_; j >= 0; j--) {
            if (!(t & (1ll << j))) continue;

            if (a[j]) t ^= a[j];
            else {
                a[j] = t;
                return;
            }
        }
    }

    void mergeFrom(const XorLinearBasis &other) {
        for (int i = 0; i <= maxl_; i++) {
            if (other.a[i]) insert(other.a[i]);
        }
    }

    static XorLinearBasis merge(const XorLinearBasis &a,
                                const XorLinearBasis &b) {
        XorLinearBasis res = a;
        for (int i = 0; i <= res.maxl_; i++) {
            if (b.a[i]) res.insert(b.a[i]);
        }
        return res;
    }

private:
    int maxl_;

    void alloc() {
        a = new int64_t[maxl_+1]{};
    }

    void dealloc() {
        delete[] a;
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


    // segment tree with single point update and range query
    // 0-indexed
    class SegmentTreeSPU {
    public:
        SegmentTreeSPU(int n) {
            nData_ = 1;
            while (nData_ < n) nData_ = nData_ << 1;
            int sz = 2 * nData_ + 1;
            data = new XorLinearBasis[sz]{};
        }

        ~SegmentTreeSPU() {
            delete[] data;
        }

        void build() {
            for (int i = nData_-1; i >= 1; i--) {
                data[i] = combine(data[2*i], data[2*i+1]);
            }
        }

        XorLinearBasis query(int a, int b) const {
            a += nData_;
            b += nData_;
            XorLinearBasis res;
            for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
                if ((a & 1) != 0) {
                    res.mergeFrom(data[a]);
                }
                if ((b & 1) == 0) {
                    res.mergeFrom(data[b]);
                }
            }
            return res;
        }

        XorLinearBasis *data;
        int nData_;
    private:
        XorLinearBasis combine(const XorLinearBasis &a,
                               const XorLinearBasis &b) const {
            return XorLinearBasis::merge(a, b);
        }
    };
public:
    const int N;
    Graph g;
    SegmentTreeSPU st;
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

    void update(int u, int64_t d) {
        int r = stIdx[u];
        //st.update(r, d);
        st.data[r+st.nData_].insert(d);
    }

    void build() {
        st.build();
    }

    XorLinearBasis queryNode(int u, int v) {
        XorLinearBasis ret = queryEdge(u, v);
        int p = lca(u, v);
        int r = stIdx[p];
        ret.mergeFrom(st.query(r, r));
        return ret;
    }

    XorLinearBasis queryEdge(int u, int v) {
        XorLinearBasis ret;
        int p = lca(u, v);
        ret.mergeFrom(queryEdgeChain(p, u));
        ret.mergeFrom(queryEdgeChain(p, v));
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

    XorLinearBasis queryEdgeChain(int anc, int u) {
        XorLinearBasis ret;
        while (u != anc) {
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                ret.mergeFrom(st.query(l, r));
                u = p;
            } else {
                int r = stIdx[u];
                ret.mergeFrom(st.query(r, r));
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
const int MAXN = 20010;
int N, Q;
int64_t G[MAXN];

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &G[i]);
    }
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N-1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        hld.addEdge(x, y);
    }
    hld.decompose();

    for (int i = 0; i < N; i++) {
        hld.update(i, G[i]);
    }
    hld.build();

    for (int i = 0; i < Q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        auto basis = hld.queryNode(x, y);
        int64_t ans = 0;
        for (int j = 60; j >= 0; j--) {
            if ((ans ^ basis.a[j]) > ans) ans ^= basis.a[j];
        }
        printf("%lld\n", ans);
    }

    return 0;
}
