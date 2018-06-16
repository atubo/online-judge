// https://www.luogu.org/problemnew/solution/P3676
// 小清新数据结构题

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
int A[MAXN];
int S[MAXN];
int64_t S0, ans;

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
            update(1, t, 0, N-1, a, b);
        }

        // query range sum in [a, b]
        int64_t query(int a, int b) {
            return query(1, a, b, 0, N-1);
        }

    private:
        // add t to range [a, b], current node range is [l, r]
        void update(int k, int t, int l, int r, int a, int b) {
            if (a > b) return;
            pushDown(k, l, r);
            if (a <= l && r <= b) {
                val[k] += int64_t(t) * (r-l+1);
                lazy[k] += t;
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
            lazy[2*k] += lazy[k];
            lazy[2*k+1] += lazy[k];
            int mid = (l + r) / 2;
            val[2*k] += (mid - l + 1) * lazy[k];
            val[2*k+1] += (r - mid) * lazy[k];
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

    int64_t queryNode(int u, int v) {
        int64_t ret = queryEdge(u, v);
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

    int64_t queryEdge(int u, int v) {
        int64_t ret = 0;
        int p = lca(u, v);
        ret += queryEdgeChain(p, u);
        ret += queryEdgeChain(p, v);
        return ret;
    }

    void preprocess() {
        dfs3(0, -1);
        for (int i = 0; i < N; i++) {
            st.update(S[i], stIdx[i], stIdx[i]);
        }
        S0 = S[0];
    }

    void query1(int x, int d) {
        ans += int64_t(d) * d * (dep[x]+1) +
            2LL * d * queryNode(0, x);
        updateNode(0, x, d);
        A[x] += d;
        S0 += d;
        //printf("%lld\n", ans);
        //printf("s0=%lld\n", S0);
    }

    void query2(int x) {
        int64_t res = ans + int64_t(S0) * S0 * (dep[x]+2)
            - 2LL * S0 * queryNode(0, x);
        printf("%lld\n", res);
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

    void dfs3(int u, int f) {
        S[u] = A[u];
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v != f) {
                dfs3(v, u);
                S[u] += S[v];
            }
        }
        ans = ans + int64_t(S[u]) * S[u];
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

    int64_t queryEdgeChain(int anc, int u) {
        int64_t ret = 0;
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

int N, Q;

int main() {
    scanf("%d%d", &N, &Q);
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        hld.addEdge(a, b);
    }
    hld.decompose();
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    hld.preprocess();

    for (int i = 0; i < Q; i++) {
        int t, x, y;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d", &x, &y);
            x--;
            hld.query1(x, y-A[x]);
        } else {
            scanf("%d", &x);
            hld.query2(x-1);
        }
    }

    return 0;
}
