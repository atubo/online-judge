// https://www.luogu.org/problemnew/show/P4315
// 月下“毛景树”

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

    // 0-indexed
    class SegmentTree {
        int N;
        int *val;
        int *lazy_set, *lazy_update;

    public:
        SegmentTree(int N_): N(N_) {
            val = new int[4*N+1]{};
            lazy_set = new int[4*N+1]{};
            lazy_update = new int[4*N+1]{};
            memset(lazy_set, -1, (4*N+1)*sizeof(int));
        }

        ~SegmentTree() {
            delete[] val;
            delete[] lazy_set;
            delete[] lazy_update;
        }
        // add t to range [a, b]
        void update(int t, int a, int b) {
            update(1, t, 0, N-1, a, b);
        }

        void setval(int t, int a, int b) {
            setval(1, t, 0, N-1, a, b);
        }

        int query(int a, int b) {
            return query(1, a, b, 0, N-1);
        }

    private:
        // add t to range [a, b], current node range is [l, r]
        void update(int k, int t, int l, int r, int a, int b) {
            if (a > b) return;
            pushDown(k, l, r);
            if (a <= l && r <= b) {
                val[k] += t;
                lazy_update[k] += t;
                return;
            }
            if (l == r) return;
            int mid = (l + r) / 2;
            if (a <= mid) update(2*k,   t, l, mid, a, b);
            if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
            val[k] = max(val[2*k], val[2*k+1]);
        }

        void setval(int k, int t, int l, int r, int a, int b) {
            if (a > b) return;
            pushDown(k, l, r);
            if (a <= l && r <= b) {
                val[k] = t;
                lazy_update[k] = 0;
                lazy_set[k] = t;
            }
            if (l == r) return;
            int mid = (l + r) / 2;
            if (a <= mid) setval(2*k,   t, l, mid, a, b);
            if (mid < b)  setval(2*k+1, t, mid+1, r, a, b);
            val[k] = max(val[2*k], val[2*k+1]);
        }

        void mergeUpdate(int k, int l) {
            if (lazy_set[l] != -1) {
                lazy_set[l] += lazy_update[k];
            } else {
                lazy_update[l] += lazy_update[k];
            }
            val[l] += lazy_update[k];
        }

        void mergeSet(int k, int l) {
            lazy_set[l] = lazy_set[k];
            val[l] = lazy_set[k];
        }

        void pushDown(int k, int l, int r) {
            if (l == r) return;
            if (lazy_set[k] == -1 && lazy_update[k] == 0) return;
            if (lazy_set[k] != -1) {
                mergeSet(k, 2*k);
                mergeSet(k, 2*k+1);
            } else {
                mergeUpdate(k, 2*k);
                mergeUpdate(k, 2*k+1);
            }
            lazy_set[k] = -1;
            lazy_update[k] = 0;
        }

        // query range sum in [a, b], current node is [L, R]
        int query(int k, int a, int b, int L, int R) {
            if (!k) return 0;
            if (b < L || a > R) return 0;
            pushDown(k, L, R);
            if (a <= L && R <= b) return val[k];
            int ret = 0;
            int mid = (L + R) / 2;
            if (a <= mid) ret = max(ret, query(2*k, a, b, L, mid));
            if (mid < b)  ret = max(ret, query(2*k+1, a, b, mid+1, R));
            return ret;
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
        Seg_size = 0;   // segment tree is 0-indexed
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

    void setNode(int u, int d) {
        int r = stIdx[u];
        st.setval(d, r, r);
    }

    void setEdge(int u, int v, int d) {
        int p = lca(u, v);
        setEdgeChain(u, p, d);
        setEdgeChain(v, p, d);
    }

    void updateEdge(int u, int v, int d) {
        int p = lca(u, v);;
        updateEdgeChain(u, p, d);
        updateEdgeChain(v, p, d);
    }

    int queryEdge(int u, int v) {
        int ret = 0;
        int p = lca(u, v);
        ret = max(ret, queryEdgeChain(p, u));
        ret = max(ret, queryEdgeChain(p, v));
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

    void setEdgeChain(int u, int anc, int val) {
        while (u != anc) {
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                st.setval(val, l, r);
                u = p;
            } else {
                int r = stIdx[u];
                st.setval(val, r, r);
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
                ret = max(ret, st.query(l, r));
                u = p;
            } else {
                int r = stIdx[u];
                ret = max(ret, st.query(r, r));
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

const int MAXN = 100010;
int N;

struct Edge {
    int u, v, w;
} E[MAXN];
int M[MAXN];

int main() {
    scanf("%d", &N);
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N-1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        hld.addEdge(u, v);
        E[i] = {u, v, w};
    }
    hld.decompose();

    for (int i = 0; i < N-1; i++) {
        int u = E[i].u;
        int v = E[i].v;
        int w = E[i].w;
        if (hld.dep[u] < hld.dep[v]) swap(u, v);
        M[i] = u;
        hld.setNode(u, w);
    }

    char cmd[10];
    while (true) {
        int u, v, w, k;
        scanf("%s", cmd);
        if (cmd[0] == 'S') break;
        if (cmd[0] == 'C' && cmd[1] == 'h') {
            scanf("%d%d", &k, &w);
            k--;
            u = M[k];
            hld.setNode(u, w);
        } else if (cmd[0] == 'C' && cmd[1] == 'o') {
            scanf("%d%d%d", &u, &v, &w);
            u--; v--;
            hld.setEdge(u, v, w);
        } else if (cmd[0] == 'A') {
            scanf("%d%d%d", &u, &v, &w);
            u--; v--;
            hld.updateEdge(u, v, w);
        } else {
            scanf("%d%d", &u, &v);
            u--; v--;
            int ans = hld.queryEdge(u, v);
            printf("%d\n", ans);
        }
    }

    return 0;
}
