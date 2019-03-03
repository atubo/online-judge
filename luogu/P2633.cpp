// https://www.luogu.org/problemnew/show/P2633
// Count on a tree

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

    class PersistentSegmentTree {
    public:
        struct Node {
            // L and R are indices of its children
            // real left and right boundaries are not kept in the node
            // to save memory
            int L, R;
            int sum;

            Node(): L(0), R(0), sum(0) {}
        };

        int N; // number of positions, index is 1-based
        int M; // number of weights, index is 0-based
        int *root;
        Node *T;
        int T_cnt = 1;

        PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
            root = new int[N+1]{};
            T = new Node[(N+1) * int(log2(M)+2)]{};
        }

        ~PersistentSegmentTree() {
            delete[] root;
            delete[] T;
        }

        // for user's convenience
        void insert(int currRootIndex, int prevRootIndex, int x, int t) {
            root[currRootIndex] = root[prevRootIndex];
            insert(root[currRootIndex], x, t, 0, M-1);
        }

        int query(int root1, int root2, int k) const {
            return query(root2, k) - query(root1, k);
        }

    private:
        // insert a new weight node x with value t
        // current range is [l, r]
        void insert(int &now, int x, int t, int l, int r) {
            T[T_cnt++] = T[now];
            now = T_cnt-1;
            T[now].sum += t;
            if (l == r) return;
            int mid = (l + r) / 2;
            if (x <= mid) insert(T[now].L, x, t, l, mid);
            else          insert(T[now].R, x, t, mid+1, r);
        }

        // query in range [0, k]
        int query(int rootIndex, int k) const {
            return query(root[rootIndex], 0, k, 0, M-1);
        }

        int query(int node, int start, int end, int l, int r) const {
            if (l > r) return 0;
            if (start <= l && r <= end) return T[node].sum;
            int mid = (l + r) / 2;
            int ret = 0;
            if (start <= mid) ret += query(T[node].L, start, end, l, mid);
            if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
            return ret;
        }
    };
public:
    const int N;
    Graph g;
    PersistentSegmentTree pst;
    vector<int> size;
    vector<int> dep;
    vector<int> rev;    // node to father-edge
    vector<int> heavy;
    vector<int> stIdx;    // node to segment tree index
    vector<int> stRev;    // segment tree index to node
    vector<int> fa; // father along heavy chain, -1 is father-edge isn't heavy
    vector<int> pa; // real father
    vector<int> top;
    vector<int> a_;
    int root;
    int Seg_size;

    HeavyLightDecomposition(int N_): N(N_), g(N_+1), pst(N_, N_) {
        size.resize(N+1);
        dep.resize(N+1);
        rev.resize(N+1);
        heavy.resize(N+1);
        stIdx.resize(N+1, -1);
        stRev.resize(N+1, 0);
        fa.resize(N+1, -1);
        pa.resize(N+1, 0);
        top.resize(N+1);

        root = 1;
        Seg_size = 1;   // segment tree is 1-indexed
    }

    void addEdge(int u, int v) {
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    void decompose() {
        dfs1(root, 0);
        top[root] = root;
        dfs2(root, 0);
    }

    void build(const vector<int> &a) {
        for (int i = 1; i <= N; i++) {
            int u = stRev[i];
            pst.insert(i, stIdx[pa[u]], a[u-1], 1);
        }
        a_ = a;
    }

    int query(int u, int v, int t) {
        int ret = queryEdge(u, v, t);
        int p = lca(u, v);
        ret += (a_[p-1] <= t);
        return ret;
    }

    int queryEdge(int u, int v, int t) {
        int ret = 0;
        int p = lca(u, v);
        ret += queryEdgeChain(p, u, t);
        ret += queryEdgeChain(p, v, t);
        return ret;
    }

    int count(int u, int v) const {
        int p = lca(u, v);
        return dep[u] + dep[v] - 2*dep[p] + 1;
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
        stRev[stIdx[u]] = u;
        pa[u] = f;

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

    int queryEdgeChain(int anc, int u, int t) {
        int ret = 0;
        while (u != anc) {
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[p];
                int r = stIdx[u];
                ret += pst.query(l, r, t);
                u = p;
            } else {
                ret += (a_[u-1] <= t);
                int fe = rev[u];
                u = g.E[fe].to;
            }
        }
        return ret;
    }

    int lca(int u, int v) const {
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
int A[MAXN], Asort[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        Asort[i] = A[i];
    }
    sort(Asort, Asort+N);
    auto endp = unique(Asort, Asort+N);
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = lower_bound(Asort, endp, A[i]) - Asort;
    }

    HeavyLightDecomposition hdl(N);
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        hdl.addEdge(u, v);
    }
    hdl.decompose();
    hdl.build(a);

    int lastans = 0;
    for (int i = 0; i < M; i++) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        u ^= lastans;
        int kmax = hdl.count(u, v);
        k = min(kmax, k);
        if (hdl.query(u, v, 0) >= k) {
            lastans = Asort[0];
            printf("%d\n", lastans);
            continue;
        }
        int lo = 0, hi = N-1;
        while (lo < hi-1) {
            int mid = (lo + hi) / 2;
            if (hdl.query(u, v, mid) >= k) hi = mid;
            else lo = mid;
        }
        lastans = Asort[hi];
        printf("%d\n", lastans);
    }

    return 0;
}
