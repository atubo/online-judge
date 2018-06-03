// https://www.luogu.org/problemnew/show/P3320
// P3320 [SDOI2015]寻宝游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, M;
bool on[MAXN];
int father[MAXN];
int64_t ans;

class HeavyLightDecomposition {
private:
    // Note graph node is 0-indexed
    class Graph {
    public:
        struct Edge {
            int next, to, wt;
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
        void addEdge(int u, int v, int w) {
            E[eidx].to = v;
            E[eidx].next = head[u];
            E[eidx].wt = w;
            head[u] = eidx++;
        }
    };


    // segment tree with single point update and range query
    // 0-indexed
    class SegmentTreeSPU {
        static const int NULL_VALUE = INT_MAX;
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
            return min(a, b);
        }
    };

    class SegmentTreeSPU2 {
        static const int NULL_VALUE = INT_MIN;
    public:
        SegmentTreeSPU2(int n) {
            nData_ = 1;
            while (nData_ < n) nData_ = nData_ << 1;
            int sz = 2 * nData_ + 1;
            data = new int[sz];
            for (int i = 0; i < sz; i++) data[i] = NULL_VALUE;
        }

        ~SegmentTreeSPU2() {
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
    vector<int> stIdx;    // node to segment tree index
    vector<int> revStIdx;   // segment tree index -> node
    vector<int> fa; // father along heavy chain, -1 is father-edge isn't heavy
    vector<int> top;
    vector<int64_t> dist;
    int root;
    int Seg_size;
    vector<set<int>> desc;
    SegmentTreeSPU trRight;
    SegmentTreeSPU2 trLeft;

    HeavyLightDecomposition(int N_):
        N(N_), g(N_), st(N_), trRight(N_), trLeft(N_) {
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        stIdx.resize(N, -1);
        revStIdx.resize(N, -1);
        fa.resize(N, -1);
        top.resize(N);
        dist.resize(N);

        root = 0;
        Seg_size = 0;   // segment tree is 1-indexed

        desc.resize(N);
    }

    void addEdge(int u, int v, int w) {
        g.addEdge(u, v, w);
        g.addEdge(v, u, w);
    }

    void decompose() {
        dfs1(root, root, 0);
        top[root] = root;
        dfs2(root, root);
    }

    void updateNode(int u, int x) {
        int r = stIdx[u];
        st.update(r, x);
    }

    void print() {
        for (int i = 0; i < N; i++) {
            int r = stIdx[i];
            int x = st.query(r, r);
            int u = (x == INT_MAX ? -2: revStIdx[x]);
            printf("%d ", u+1);
        }
        printf("\n");
    }


    void process(int u) {
        if (!on[u]) {
            turnOn(u);
        } else {
            turnOff(u);
        }
        //print();
    }

private:
    void dfs1(int u, int f, int64_t d) {
        int mx = -1, e = -1;
        size[u] = 1;
        dist[u] = d;

        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            if (v == f) continue;
            dep[v] = dep[u] + 1;
            rev[v] = eidx ^ 1;
            dfs1(v, u, d + w);
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
        revStIdx[Seg_size-1] = u;

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
        int ret = INT_MAX;
        while (u != anc) {
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                ret = min(ret, st.query(l, r));
                u = p;
            } else {
                int r = stIdx[u];
                ret = min(ret, st.query(r, r));
                int fe = rev[u];
                u = g.E[fe].to;
            }
        }
        return ret == INT_MAX ? -1 : revStIdx[ret];
    }

    void addPath(int u, int f) {
        if (u != f) desc[f].insert(u);
        father[u] = f;
        ans += 2 * (dist[u] - dist[f]);
    }

    void removePath(int u, int f) {
        desc[f].erase(u);
        father[u] = u;
        ans -= 2 * (dist[u] - dist[f]);
    }

    void removeNode(int u) {
        updateNode(u, INT_MAX);
    }

    void addNode(int u) {
        updateNode(u, stIdx[u]);
    }

    bool emptyTreasure() const {
        int x = trLeft.query(0, N-1);
        return x == INT_MIN;
    }

    void insertTreasure(int u) {
        int r = stIdx[u];
        trLeft.update(r, r);
        trRight.update(r, r);
    }

    void removeTreasure(int u) {
        int r = stIdx[u];
        trLeft.update(r, INT_MIN);
        trRight.update(r, INT_MAX);
    }

    int nearestTreasure(int u) {
        int r = stIdx[u];
        int rv1 = trLeft.query(0, r);
        int rv2 = trRight.query(r, N-1);
        if (rv1 != INT_MIN && rv2 != INT_MAX) {
            int v1 = revStIdx[rv1], v2 = revStIdx[rv2];
            if (dep[lca(u, v1)] > dep[lca(u, v2)]) return v1;
            else return v2;
        } else if (rv1 != INT_MIN) {
            return revStIdx[rv1];
        } else {
            return revStIdx[rv2];
        }
    }

    void turnOn(int u) {
        on[u] = true;

        if (emptyTreasure()) {
            insertTreasure(u);
            addPath(u, u);
            addNode(u);
            printf("%lld\n",ans);
            return;
        }

        int v = nearestTreasure(u);
        insertTreasure(u);
        addNode(u);

        int p = lca(u, v);
        if (u != p) {
            addPath(u, p);
            addNode(p);
        }

        v = queryEdgeChain(p, v);
        if (v != -1) {
            int fv = father[v];
            if (dep[fv] > dep[p]) {
                addPath(fv, p);
            } else if (dep[fv] < dep[p]) {
                removePath(v, fv);
                addPath(v, p);
                addPath(p, fv);
            }
        }
        printf("%lld\n", ans);
    }

    void turnOff(int u) {
        on[u] = false;

        int v = u;
        while (v != father[v] && desc[v].empty() && !on[v]) {
            int f = father[v];
            removePath(v, f);
            removeNode(v);
            v = f;
        }

        while (v == father[v] && desc[v].size() == 1 && !on[v]) {
            int c = *desc[v].begin();
            removePath(c, v);
            removeNode(v);
            v = c;
        }
        if (v == father[v] && desc[v].empty() && !on[v]) removeNode(v);

        removeTreasure(u);
        printf("%lld\n", ans);
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
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) father[i] = i;

    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N-1; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        x--; y--;
        hld.addEdge(x, y, z);
    }
    hld.decompose();

    for (int i = 0; i < M; i++) {
        int u;
        scanf("%d", &u);
        u--;
        hld.process(u);
    }

    return 0;
}
