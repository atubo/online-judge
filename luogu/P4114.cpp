// https://www.luogu.org/problemnew/show/P4114
// Qtree1

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

    // segment tree with single point update and range query
    class SegmentTree {
        static const int NULL_VALUE = INT_MIN;
    public:
        SegmentTree(int n) {
            nData_ = 1;
            while (nData_ < n) nData_ = nData_ << 1;
            int sz = 2 * nData_ + 1;
            data = new int[sz]{NULL_VALUE};
        }

        ~SegmentTree() {
            delete[] data;
        }

        void update(int i, int value) {
            i += nData_;
            data[i] = value;
            for (; i > 1; i >>= 1) {
                int newVal = combine(data[i], data[i^1]);
                if (data[i>>1] == newVal) break;
                data[i>>1] = newVal;
            }
        }

        int query(int a, int b) const {
            a += nData_;
            b += nData_;
            int res = NULL_VALUE;
            for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
                if ((a & 1) != 0) {
                    res = combine(res, data[a]);
                }
                if ((b & 1) == 0) {
                    res = combine(res, data[b]);
                }
            }
            return res;
        }

        int query() const {
            return data[1];
        }
    private:
        int *data;
        int nData_;
        int combine(int a, int b) const {
            return max(a, b);
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
    vector<int> stIdx;    // edge to segment tree index
    vector<int> fa;
    vector<int> top;
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

        root = 0;
        Seg_size = 0;
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

    void update(int u, int v, int d) {
        assert(abs(dep[u] - dep[v]) == 1);
        if (dep[u] > dep[v]) swap(u, v);
        int r = stIdx[v];
        st.update(r, d);
    }

    int queryEdge(int u, int v) {
        int ret = INT_MIN;
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

    int queryEdgeChain(int anc, int u) {
        int ret = INT_MIN;
        while (u != anc) {
            int fe = rev[u];
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
};

int main() {
    scanf("%d", &N);
    vector<Edge> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        edges[i] = {u, v, w};
    }

    HeavyLightDecomposition hld(N);
    for (const auto &e: edges) {
        hld.addEdge(e.u, e.v);
    }
    hld.decompose();

    for (const auto &e: edges) {
        hld.update(e.u, e.v, e.w);
    }

    while (true) {
        char cmd[10];
        int x, y;
        scanf("%s", cmd);
        if (cmd[0] == 'D') break;
        scanf("%d%d", &x, &y);
        if (cmd[0] == 'C') {
            hld.update(edges[x-1].u, edges[x-1].v, y);
        } else {
            if (x == y) {
                printf("0\n");
            } else {
                int ans = hld.queryEdge(x-1, y-1);
                printf("%d\n", ans);
            }
        }
    }

    return 0;
}
