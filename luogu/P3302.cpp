// https://www.luogu.org/problemnew/show/P3302
// [SDOI2013]森林

#include <bits/stdc++.h>
using namespace std;

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

struct Query {
    int x, y, k;
};


const int MAXN = 80010;
int N, M, T;
int A[MAXN];
vector<int> B;
Query queries[MAXN];

int Hash(int x) {
    return lower_bound(B.begin(), B.end(), x) - B.begin();
}

class HeavyLightDecomposition {
private:
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

        // query in range [start, end]
        int query(int rootIndex, int start, int end) {
            return query(root[rootIndex], start, end, 0, M-1);
        }

        int queryKth(int u, int v, int p, int pfa, int k) {
            return queryKth(u, v, p, pfa, k, 0, M-1);
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

        int query(int node, int start, int end, int l, int r) {
            if (l > r) return 0;
            if (start <= l && r <= end) return T[node].sum;
            int mid = (l + r) / 2;
            int ret = 0;
            if (start <= mid) ret += query(T[node].L, start, end, l, mid);
            if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
            return ret;
        }

        int lft(int u) const {return T[u].L;}
        int rgt(int u) const {return T[u].R;}

        int queryKth(int u, int v, int p, int pfa, int k, int l, int r) {
            if (l == r) return l;
            int mid = (l + r) / 2;
            int order = T[lft(u)].sum - T[lft(pfa)].sum +
                T[lft(v)].sum - T[lft(p)].sum;
            if (order >= k) {
                return queryKth(lft(u), lft(v), lft(p), lft(pfa), k, l, mid);
            } else {
                return queryKth(rgt(u), rgt(v), rgt(p), rgt(pfa), k-order,
                                mid+1, r);
            }
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
    vector<int> stIdx;    // edge to segment tree index
    vector<int> fa;
    vector<int> top;
    vector<array<int, 17>> st;
    vector<int> son;
    vector<bool> vis;
    int root;
    int Seg_size;

    HeavyLightDecomposition(int N_): N(N_), g(N_), pst(N_, N_) {
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        stIdx.resize(N, -1);
        fa.resize(N);
        top.resize(N);
        st.resize(N);
        son.resize(N);
        vis.resize(N);

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

    void dfs3(int u, int f, const vector<int> &val) {
        if (u == root) {
            pst.insert(stIdx[u], 0, val[u], 1);
        } else {
            pst.insert(stIdx[u], stIdx[f], val[u], 1);
        }

        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v == f) continue;
            dfs3(v, u, val);
        }
    }

    void dfs4(int x, int father, int rt) {
        st[x][0] = father;
        for (int k = 1; k <= 16; k++) {
            st[x][k] = st[st[x][k-1]][k-1];
        }
        son[rt]++;
        dep[x] = dep[father] + 1;
        fa[x] = father;
        vis[x] = true;
        pst.insert(x, father, Hash(A[x]), 1);
        for (int eidx = g.head[x]; ~eidx; eidx = g.E[eidx].next) {
            int u = g.E[eidx].to;
            if (u == father) continue;
            dfs4(u, x, rt);
        }
    }

    int query(int u, int v, int k) {
        int p = lca(u, v);
        int pfa = (p == root ? 0 : stIdx[fa[p]]);
        return pst.queryKth(stIdx[u], stIdx[v], stIdx[p], pfa, k);
    }

#if 0
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
#endif

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

#if 0
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
#endif


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

void dfs(const Graph &g, int u, vector<bool> &vis) {
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (!vis[v]) dfs(g, v, vis);
    }
}

int main() {
    int ts;
    scanf("%d", &ts);
    scanf("%d%d%d", &N, &M, &T);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    Graph g(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("u=%d v=%d\n", u, v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    for (int i = 0; i < T; i++) {
        char tp[10];
        int x, y, k;
        scanf("%s", tp);
        printf("type=%s\n", tp);
        if (tp[0] == 'Q') {
            scanf("%d%d%d", &x, &y, &k);
            queries[i] = {x-1, y-1, k};
        } else {
            scanf("%d%d", &x, &y);
            x--; y--;
            g.addEdge(x, y);
            g.addEdge(y, x);
        }
    }

    vector<int> roots;
    vector<bool> vis(N, false);
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            roots.push_back(i);
            dfs(g, i, vis);
        }
    }

    for (int u: roots) {
        printf("%d ", u);
    }
    printf("\n");

    return 0;
}
