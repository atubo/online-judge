// https://www.luogu.org/problemnew/solution/P3313
// [SDOI2014]旅行

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, Q;
int W[MAXN], C[MAXN];


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

    class SegmentForest {
        struct Node {
            // L and R are indices of its children
            // real left and right boundaries are not kept in the node itself
            int L = 0, R = 0;
            int sum = 0, maxval = 0;
        };

        int N;  // number of trees, 0-indexed
        int M;  // number of leaves of each tree, 0-indexed

        int *root;
        Node *T;
        int T_cnt = 1;

    public:
        SegmentForest(int N_, int M_, int numInsertions): N(N_), M(M_) {
            root = new int[N]{};

            // T[0] is null node, so we add 1
            int cap = 1 + numInsertions * int(log2(M) + 2);
            T = new Node[cap]{};
        }

        ~SegmentForest() {
            delete[] root;
            delete[] T;
        }

        // add t to position x of tree rootIndex
        void insert(int rootIndex, int x, int t) {
            insert(root[rootIndex], x, t, 0, M-1);
        }

        // query in range [start, end]
        int query(int rootIndex, int start, int end) const {
            return query(root[rootIndex], start, end, 0, M-1);
        }

        int queryMax(int rootIndex, int start, int end) const {
            return queryMax(root[rootIndex], start, end, 0, M-1);
        }

    private:
        // insert a new node x with value t
        // curret range is [l, r]
        void insert(int &now, int x, int t, int l, int r) {
            if (!now) now = T_cnt++;
            T[now].sum += t;
            if (l == r) {
                T[now].maxval += t;
                return;
            }
            int mid = (l + r) / 2;
            if (x <= mid) insert(T[now].L, x, t, l, mid);
            else          insert(T[now].R, x, t, mid+1, r);
            T[now].maxval = max(T[T[now].L].maxval,
                                T[T[now].R].maxval);
        }

        int query(int node, int start, int end, int l, int r) const {
            if (node == 0) return 0;
            if (l > r) return 0;
            if (start <= l && r <= end) return T[node].sum;
            int mid = (l + r) / 2;
            int ret = 0;
            if (start <= mid) ret += query(T[node].L, start, end, l, mid);
            if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
            return ret;
        }

        int queryMax(int node, int start, int end, int l, int r) const {
            if (node == 0) return 0;
            if (l > r) return 0;
            if (start <= l && r <= end) return T[node].maxval;
            int mid = (l + r) / 2;
            int ret = 0;
            if (start <= mid) {
                ret = max(ret, queryMax(T[node].L, start, end, l, mid));
            }
            if (mid+1 <= end) {
                ret = max(ret, queryMax(T[node].R, start, end, mid+1, r));
            }
            return ret;
        }
    };

public:
    const int N;
    Graph g;
    SegmentForest sf;
    vector<int> size;
    vector<int> dep;
    vector<int> rev;    // node to father-edge
    vector<int> heavy;
    vector<int> stIdx;    // edge to segment tree index
    vector<int> fa;
    vector<int> top;
    int root;
    int Seg_size;

    HeavyLightDecomposition(int N_): N(N_), g(N_), sf(N_, MAXN, MAXN) {
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        stIdx.resize(N, -1);
        fa.resize(N);
        top.resize(N);

        root = 1;
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
        for (int i = 1; i < N; i++) {
            sf.insert(C[i], stIdx[i], W[i]);
        }
    }

    void updateReligion(int x, int c) {
        int u = stIdx[x];
        int oldc = C[x];
        sf.insert(oldc, u, -W[x]);
        sf.insert(c, u, W[x]);
        C[x] = c;
    }

    void updateScore(int x, int w) {
        int u = stIdx[x];
        int oldw = W[x];
        sf.insert(C[x], u, w - oldw);
        W[x] = w;
    }

    int queryNode(int u, int v) {
        assert(C[u] == C[v]);
        int c = C[u];
        int ret = queryEdge(c, u, v);
        int p = lca(u, v);
        int r = stIdx[p];
        ret += sf.query(c, r, r);
        return ret;
    }

    int queryNodeMax(int u, int v) {
        assert(C[u] == C[v]);
        int c = C[u];
        int ret = queryEdgeMax(c, u, v);
        int p = lca(u, v);
        int r = stIdx[p];
        ret = max(ret, sf.queryMax(c, r, r));
        return ret;
    }

    int queryEdge(int c, int u, int v) {
        int ret = 0;
        int p = lca(u, v);
        ret += queryEdgeChain(c, p, u);
        ret += queryEdgeChain(c, p, v);
        return ret;
    }

    int queryEdgeMax(int c, int u, int v) {
        int ret = 0;
        int p = lca(u, v);
        ret = max(ret, queryEdgeChainMax(c, p, u));
        ret = max(ret, queryEdgeChainMax(c, p, v));
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
    }

    int queryEdgeChain(int c, int anc, int u) {
        int ret = 0;
        while (u != anc) {
            int fe = rev[u];
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                ret += sf.query(c, l, r);
                u = p;
            } else {
                int r = stIdx[u];
                ret += sf.query(c, r, r);
                u = g.E[fe].to;
            }
        }
        return ret;
    }

    int queryEdgeChainMax(int c, int anc, int u) {
        int ret = 0;
        while (u != anc) {
            int fe = rev[u];
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                ret = max(ret, sf.queryMax(c, l, r));
                u = p;
            } else {
                int r = stIdx[u];
                ret = max(ret, sf.query(c, r, r));
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

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &W[i], &C[i]);
    }

    HeavyLightDecomposition hld(N+1);
    for (int i = 0; i < N-1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        hld.addEdge(x, y);
    }
    hld.decompose();

    char cmd[10];
    int x, y;
    for (int i = 0; i < Q; i++) {
        scanf("%s%d%d", cmd, &x, &y);
        if (cmd[0] == 'C') {
            if (cmd[1] == 'C') {
                hld.updateReligion(x, y);
            } else {
                hld.updateScore(x, y);
            }
        } else {
            if (cmd[1] == 'S') {
                printf("%d\n", hld.queryNode(x, y));
            } else {
                printf("%d\n", hld.queryNodeMax(x, y));
            }
        }
    }

    return 0;
}
