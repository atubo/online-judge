// https://www.luogu.org/problemnew/show/P2590
// [ZJOI2008]树的统计

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
        static const int NULL_SUM = 0;
        static const int NULL_MAX = INT_MIN;
    public:
        SegmentTree(int n) {
            nData_ = 1;
            while (nData_ < n) nData_ = nData_ << 1;
            int sz = 2 * nData_ + 1;
            dataSum = new int[sz]{NULL_SUM};
            dataMax = new int[sz]{NULL_MAX};
        }

        ~SegmentTree() {
            delete[] dataSum;
            delete[] dataMax;
        }

        void update(int i, int value) {
            i += nData_;
            dataSum[i] = value;
            dataMax[i] = value;
            for (; i > 1; i >>= 1) {
                int newVal = combineSum(dataSum[i], dataSum[i^1]);
                dataSum[i>>1] = newVal;

                newVal = combineMax(dataMax[i], dataMax[i^1]);
                dataMax[i>>1] = newVal;
            }
        }

        int querySum(int a, int b) const {
            a += nData_;
            b += nData_;
            int res = NULL_SUM;
            for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
                if ((a & 1) != 0) {
                    res = combineSum(res, dataSum[a]);
                }
                if ((b & 1) == 0) {
                    res = combineSum(res, dataSum[b]);
                }
            }
            return res;
        }

        int queryMax(int a, int b) const {
            a += nData_;
            b += nData_;
            int res = NULL_MAX;
            for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
                if ((a & 1) != 0) {
                    res = combineMax(res, dataMax[a]);
                }
                if ((b & 1) == 0) {
                    res = combineMax(res, dataMax[b]);
                }
            }
            return res;
        }

    private:
        int *dataSum;
        int *dataMax;
        int nData_;
        int combineSum(int a, int b) const {
            return a + b;
        }

        int combineMax(int a, int b) const {
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

    void updateNode(int u, int d) {
        int id = stIdx[u];
        st.update(id, d);
    }

    int queryNodeSum(int u, int v) {
        int ret = queryEdgeSum(u, v);
        int p = lca(u, v);
        int r = stIdx[p];
        ret += st.querySum(r, r);
        return ret;
    }

    int queryNodeMax(int u, int v) {
        int ret = queryEdgeMax(u, v);
        int p = lca(u, v);
        int r = stIdx[p];
        ret = max(ret, st.queryMax(r, r));
        return ret;
    }

    int queryEdgeSum(int u, int v) {
        int ret = 0;
        int p = lca(u, v);
        ret += queryEdgeChainSum(p, u);
        ret += queryEdgeChainSum(p, v);
        return ret;
    }

    int queryEdgeMax(int u, int v) {
        int ret = INT_MIN;
        int p = lca(u, v);
        ret = max(ret, queryEdgeChainMax(p, u));
        ret = max(ret, queryEdgeChainMax(p, v));
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

    int queryEdgeChainSum(int anc, int u) {
        int ret = 0;
        while (u != anc) {
            int fe = rev[u];
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                ret += st.querySum(l, r);
                u = p;
            } else {
                int r = stIdx[u];
                ret += st.querySum(r, r);
                u = g.E[fe].to;
            }
        }
        return ret;
    }

    int queryEdgeChainMax(int anc, int u) {
        int ret = INT_MIN;
        while (u != anc) {
            int fe = rev[u];
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                ret = max(ret, st.queryMax(l, r));
                u = p;
            } else {
                int r = stIdx[u];
                ret = max(ret, st.queryMax(r, r));
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

const int MAXN = 30010;
int N, Q;

int main() {
    scanf("%d", &N);
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        hld.addEdge(a, b);
    }
    hld.decompose();

    for (int i = 0; i < N; i++) {
        int w;
        scanf("%d", &w);
        hld.updateNode(i, w);
    }

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        char cmd[10];
        int x, y;
        scanf("%s%d%d", cmd, &x, &y);
        if (cmd[0] == 'C') {
            hld.updateNode(x-1, y);
        } else if (cmd[1] == 'M') {
            int ans = hld.queryNodeMax(x-1, y-1);
            printf("%d\n", ans);
        } else {
            int ans = hld.queryNodeSum(x-1, y-1);
            printf("%d\n", ans);
        }
    }

    return 0;
}
