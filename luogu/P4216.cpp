// https://www.luogu.org/problem/P4216
// [SCOI2015]情报传递

#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
public:
    // 1-indexed
    FenwickTree(int size): n_(size) {
        tree_ = new int[n_+1]{};
    }

    ~FenwickTree() {
        delete[] tree_;
    }

    void clear() {
        memset(tree_, 0, (n_+1) * sizeof(int));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= n_) {
            tree_[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree_[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

private:
    int* tree_;
    const int n_;
};

const int MAXN = 200010;
bool D[MAXN];

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

public:
    const int N;
    Graph g;
    FenwickTree ft;
    vector<int> size;
    vector<int> dep;
    vector<int> rev;    // node to father-edge
    vector<int> heavy;
    vector<int> stIdx;    // node to segment tree index
    vector<int> fa; // father along heavy chain, -1 is father-edge isn't heavy
    vector<int> top;
    int root;
    int Seg_size;

    HeavyLightDecomposition(int N_): N(N_), g(N_), ft(N_) {
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

    // at day t, let agent u collect intel
    void collect(int u) {
        if (D[u]) return;
        int x = stIdx[u];
        ft.set(x, 1);
        D[u] = true;
    }

    // pass intel from u to v
    pair<int, int> pass(int u, int v) {
        int p = lca(u, v);
        int x = dep[u] + dep[v] - 2*dep[p] + 1;
        int y = 0;
        y += queryEdgeChain(p, u);
        y += queryEdgeChain(p, v);
        int r = stIdx[p];
        y += ft.get(r, r);
        return make_pair(x, y);
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

    int queryEdgeChain(int anc, int u) {
        int ret = 0;
        while (u != anc) {
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                ret += ft.get(l, r);
                u = p;
            } else {
                int r = stIdx[u];
                ret += ft.get(r, r);
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
struct Task {
    int k, x, y, t, id;
    bool operator < (const Task &other) const {
        if (t != other.t) return t < other.t;
        if (k != other.k) return k < other.k;
        return id < other.id;
    }
} T[MAXN];
pair<int, int> ans[MAXN];

int main() {
    scanf("%d", &N);
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        x--;
        if (x != -1) {
            hld.addEdge(i, x);
        } else {
            hld.root = i;
        }
    }
    hld.decompose();
    scanf("%d", &Q);

    int cnt = 0;
    for (int t = 0; t < Q; t++) {
        int k, x, y, c;
        scanf("%d", &k);
        if (k == 1) {
            scanf("%d%d%d", &x, &y, &c);
            x--; y--;
            T[t] = {1, x, y, t-c, cnt++};
        } else {
            scanf("%d", &x);
            x--;
            T[t] = {2, x, -1, t, -1};
        }
    }
    sort(T, T+Q);

    for (int i = 0; i < Q; i++) {
        if (T[i].k == 1) {
            ans[T[i].id] = hld.pass(T[i].x, T[i].y);
        } else {
            hld.collect(T[i].x);
        }
    }

    for (int i = 0; i < cnt; i++) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }

    return 0;
}
