// https://www.luogu.org/problemnew/show/P2934
// [USACO09JAN]安全出行Safe Travel

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
        int *lazy;

    public:
        SegmentTree(int N_): N(N_) {
            lazy = new int[4*N]{};
            memset(lazy, 0x7F, 4*N*sizeof(int));
        }

        ~SegmentTree() {
            delete[] lazy;
        }
        // set t to range [a, b]
        void update(int t, int a, int b) {
            update(1, t, 0, N-1, a, b);
        }

        // query value at position a
        int query(int a) {
            return query(1, a, 0, N-1);
        }

    private:
        // set t to range [a, b], current node range is [l, r]
        void update(int k, int t, int l, int r, int a, int b) {
            if (a > b) return;
            if (t >= lazy[k]) return;
            pushDown(k, l, r);
            if (a <= l && r <= b) {
                lazy[k] = t;
                return;
            }
            if (l == r) return;
            int mid = (l + r) / 2;
            if (a <= mid) update(2*k,   t, l, mid, a, b);
            if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        }

        void pushDown(int k, int l, int r) {
            if (l == r) return;
            if (lazy[k] == INT_MAX) return;
            lazy[2*k] = min(lazy[2*k], lazy[k]);
            lazy[2*k+1] = min(lazy[2*k+1], lazy[k]);
            lazy[k] = INT_MAX;
        }

        int query(int k, int a, int L, int R) {
            if (!k) return INT_MAX;
            if (a > R) return INT_MAX;
            pushDown(k, L, R);
            if (L == R) return lazy[k];
            int mid = (L + R) / 2;
            int ret;
            if (a <= mid) ret = query(2*k, a, L, mid);
            else          ret = query(2*k+1, a, mid+1, R);
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

    int query(int u) {
        int r = stIdx[u];
        return st.query(r);
    }

    void updateEdge(int u, int v, int d) {
        int p = lca(u, v);;
        updateEdgeChain(u, p, d);
        updateEdgeChain(v, p, d);
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
int D[MAXN], PREV[MAXN];
bool inq[MAXN];

void spfa(const Graph &g) {
    memset(D, 0x7F, sizeof(D));
    memset(PREV, -1, sizeof(PREV));
    D[0] = 0;
    queue<int> q;
    q.push(0);
    inq[0] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int d = D[u] + g.E[eidx].wt;
            if (D[v] > d) {
                D[v] = d;
                PREV[v] = u;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        a--; b--;
        g.addEdge(a, b, t);
        g.addEdge(b, a, t);
    }

    spfa(g);

    HeavyLightDecomposition hld(N);
    for (int i = 1; i < N; i++) {
        hld.addEdge(i, PREV[i]);
    }

    hld.decompose();
    for (int u = 0; u < N; u++) {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (PREV[u] == v || PREV[v] == u) continue;
            int d = D[u] + D[v] + g.E[eidx].wt;
            if (u < v) hld.updateEdge(u, v, d);
        }
    }
    for (int u = 1; u < N; u++) {
        int d = hld.query(u);
        int ans = -1;
        if (d < 2e9) ans = -D[u] + d;
        printf("%d\n", ans);
    }
    return 0;
}
