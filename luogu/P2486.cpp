// https://www.luogu.org/problemnew/show/P2486
// [SDOI2011]染色

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
    class SegmentTreeDelta {
        int N;
        int64_t *val, *lazy;

    public:
        SegmentTreeDelta(int N_): N(N_) {
            val = new int64_t[4*N]{};
            lazy = new int64_t[4*N]{};
            memset(lazy, -1, 4*N*sizeof(int64_t));
        }

        ~SegmentTreeDelta() {
            delete[] val;
            delete[] lazy;
        }
        // set range [a, b] to t
        void update(int t, int a, int b) {
            update(1, t, 1, N, a, b);
        }

        // query range sum in [a, b]
        int64_t query(int a, int b) {
            return query(1, a, b, 1, N);
        }

    private:
        // set range [a, b] to t, current node range is [l, r]
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

    // 1-indexed
    class SegmentTreeColor {
        int N;
        int64_t *val, *lazy;

    public:
        SegmentTreeColor(int N_): N(N_) {
            val = new int64_t[4*N]{};
            lazy = new int64_t[4*N]{};
        }

        ~SegmentTreeColor() {
            delete[] val;
            delete[] lazy;
        }
        // change range[a, b] to t
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
            if (!lazy[k] || l == r) return;
            lazy[2*k] = lazy[k];
            lazy[2*k+1] = lazy[k];
            int mid = (l + r) / 2;
            val[2*k] = (mid - l + 1) * lazy[k];
            val[2*k+1] = (r - mid) * lazy[k];
            lazy[k] = 0;
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
    SegmentTreeColor stColor;
    SegmentTreeDelta stDelta;
    vector<int> size;
    vector<int> dep;
    vector<int> rev;    // node to father-edge
    vector<int> heavy;
    vector<int> stIdx;    // node to segment tree index
    vector<int> fa;
    vector<int> top;
    int root;
    int Seg_size;

    HeavyLightDecomposition(int N_): N(N_), g(N_), stColor(N_), stDelta(N_) {
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        stIdx.resize(N, -1);
        fa.resize(N, -1);
        top.resize(N);

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

    void paint(int u, int v, int d) {
        paintEdge(u, v, d);
        int p = lca(u, v);
        int r = stIdx[p];
        stColor.update(d, r, r);
    }

    void paintEdge(int u, int v, int d) {
        int p = lca(u, v);
        paintEdgeChain(u, p, d);
        paintEdgeChain(v, p, d);
    }

    int queryColor(int u) {
        int r = stIdx[u];
        return stColor.query(r, r);
    }

    void updateDelta(int u, int v) {
        int p = lca(u, v);
        updateDeltaEdgeChain(u, p);
        updateDeltaEdgeChain(v, p);
        int fp = fa[p];
        if (fp != -1) {
            if (queryColor(p) != queryColor(fp)) {
                stDelta.update(1, stIdx[p], stIdx[p]);
            } else {
                stDelta.update(0, stIdx[p], stIdx[p]);
            }
        }
    }

    int queryDelta(int u, int v) {
        int p = lca(u, v);
        int ans = queryDeltaEdgeChain(p, u);
        ans += queryDeltaEdgeChain(p, v);
        return ans + 1;
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

    void paintEdgeChain(int u, int anc, int val) {
        while (u != anc) {
            int fe = rev[u];
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                stColor.update(val, l, r);
                u = p;
            } else {
                int r = stIdx[u];
                stColor.update(val, r, r);
                u = g.E[fe].to;
            }
        }
    }

    void updateHeavyChild(int u) {
        int v = heavyChild(u);
        if (v) {
            int rv = stIdx[v];
            int ru = stIdx[u];
            if (stColor.query(rv, rv) != stColor.query(ru, ru)) {
                stDelta.update(1, rv, rv);
            } else {
                stDelta.update(0, rv, rv);
            }
        }
    }

    void updateDeltaEdgeChain(int u, int anc) {
        while (u != anc) {
            updateHeavyChild(u);
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                stDelta.update(0, l, r);
                u = p;
            } else {
                int fe = rev[u];
                u = g.E[fe].to;
            }
        }
        updateHeavyChild(u);
    }

    int queryDeltaEdgeChain(int anc, int u) {
        int ret = 0;
        while (u != anc) {
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                ret += stDelta.query(l, r);
                u = p;
            } else {
                int fe = rev[u];
                int fu = g.E[fe].to;
                ret += (queryColor(u) != queryColor(fu));
                u = fu;
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

const int MAXN = 100010;
int N, M;
int color[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &color[i]);
    }
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        hld.addEdge(u, v);
    }
    hld.decompose();
    for (int i = 0; i < N; i++) {
        hld.paint(i, i, color[i]);
    }
    for (int i = 0; i < N; i++) {
        int v = hld.fa[i];
        if (v != -1) {
            if (hld.queryColor(i) != hld.queryColor(v)) {
                hld.stDelta.update(1, hld.stIdx[i], hld.stIdx[i]);
            }
        }
    }
    for (int i = 0; i < M; i++) {
        char cmd[10];
        int a, b, c;
        scanf("%s%d%d", cmd, &a, &b);
        a--; b--;
        if (cmd[0] == 'C') {
            scanf("%d", &c);
            hld.paint(a, b, c);
            hld.updateDelta(a, b);
#if 0
            for (int u = 0; u < N; u++) {
                printf("%d ", hld.queryColor(u));
            }
            printf("\n");
            for (int u = 0; u < N; u++) {
                printf("%lld ", hld.stDelta.query(hld.stIdx[u], hld.stIdx[u]));
            }
            printf("\n");
#endif
        } else {
            printf("%d\n", hld.queryDelta(a, b));
        }
    }

    return 0;
}
