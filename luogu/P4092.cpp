// https://www.luogu.org/problemnew/show/P4092
// [HEOI2016/TJOI2016]树

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
    class SegmentTreeSPU {
        static const int NULL_VALUE = -1;
    public:
        SegmentTreeSPU(int n) {
            nData_ = 1;
            while (nData_ < n) nData_ = nData_ << 1;
            int sz = 2 * nData_ + 1;
            data = new int[sz];
            for (int i = 0; i < sz; i++) data[i] = NULL_VALUE;
        }

        ~SegmentTreeSPU() {
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
    SegmentTreeSPU st;
    vector<int> size;
    vector<int> dep;
    vector<int> rev;    // node to father-edge
    vector<int> heavy;
    vector<int> stIdx;    // edge to segment tree index
    vector<int> stRevIdx;
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
        stRevIdx.resize(N);
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
        for (int i = 0; i < N; i++) {
            stRevIdx[stIdx[i]] = i;
        }
    }

    void mark(int u) {
        int r = stIdx[u];
        st.update(r, r);
    }

    int query(int u) {
        int ret = queryEdgeChain(0, u);
        int r = stIdx[0];
        ret = max(ret, st.query(r, r));
        return stRevIdx[ret] + 1;
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
        int ret = -1;
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

int N, Q;

int main() {
    scanf("%d%d", &N, &Q);
    HeavyLightDecomposition hld(N);

    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        hld.addEdge(u, v);
    }
    hld.decompose();
    hld.mark(0);

    char cmd[10];
    for (int i = 0; i < Q; i++) {
        int u;
        scanf("%s%d", cmd, &u);
        u--;
        if (cmd[0] == 'C') {
            hld.mark(u);
        } else {
            printf("%d\n", hld.query(u));
        }
    }

    return 0;
}
