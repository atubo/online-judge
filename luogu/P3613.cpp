// https://www.luogu.org/problemnew/show/P3613
// 睡觉困难综合征

#include <bits/stdc++.h>
using namespace std;

struct Data {
    uint64_t a, b, c, d;
    bool operator == (const Data &other) const {
        return a == other.a &&
            b == other.b &&
            c == other.c &&
            d == other.d;
    }
};

const uint64_t ALL_ONE = std::numeric_limits<uint64_t>::max();
constexpr Data NULL_VALUE = {0, ALL_ONE, 0, ALL_ONE};

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
    // 0-indexed
    class SegmentTreeSPU {
    public:

        SegmentTreeSPU(int n) {
            nData_ = 1;
            while (nData_ < n) nData_ = nData_ << 1;
            int sz = 2 * nData_ + 1;
            data = new Data[sz];
            for (int i = 0; i < sz; i++) data[i] = NULL_VALUE;
        }

        ~SegmentTreeSPU() {
            delete[] data;
        }

        void update(int i, const Data &d) {
            i += nData_;
            data[i] = d;
            for (; i > 1; i >>= 1) {
                Data newVal = (((i & 1) == 0) ?
                               combine(data[i], data[i^1]):
                               combine(data[i^1], data[i]));
                if (data[i>>1] == newVal) break;
                data[i>>1] = newVal;
            }
        }

        Data query(int a, int b) const {
            a += nData_;
            b += nData_;
            Data left = NULL_VALUE, right = NULL_VALUE;
            for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
                if ((a & 1) != 0) {
                    left = combine(left, data[a]);
                }
                if ((b & 1) == 0) {
                    right = combine(data[b], right);
                }
            }
            return combine(left, right);
        }

    private:
        Data *data;
        int nData_;
    public:
        static Data combine(const Data &a, const Data &b) {
            Data ret;
            ret.a = (~a.a&b.a)|(a.a&b.b);
            ret.b = (~a.b&b.a)|(a.b&b.b);
            ret.c = (~b.c&a.c)|(b.c&a.d);
            ret.d = (~b.d&a.c)|(b.d&a.d);
            return ret;
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
    vector<int> fa; // father along heavy chain, -1 is father-edge isn't heavy
    vector<int> top;
    int root;
    int Seg_size;

    HeavyLightDecomposition(int N_, int K_):
        N(N_), g(N_), st(N_) {
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        stIdx.resize(N, -1);
        fa.resize(N, -1);
        top.resize(N);

        root = 0;
        Seg_size = 0;
    }

    ~HeavyLightDecomposition() {
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

    void updateNode(int x, int y, uint64_t z) {
        Data d;
        switch (y) {
            case 1:
                d = {0, z, 0, z};
                break;
            case 2:
                d = {z, ALL_ONE, z, ALL_ONE};
                break;
            case 3:
                d = {z, ~z, z, ~z};
                break;
            default:
                break;
        }
        int r = stIdx[x];
        st.update(r, d);
    }

    Data queryNode(int u, int v) {
        int p = lca(u, v);
        Data d = queryEdgeChain(p, u);
        d = {d.c, d.d, d.a, d.b};
        int r = stIdx[p];
        d = SegmentTreeSPU::combine(d, st.query(r, r));
        d = SegmentTreeSPU::combine(d, queryEdgeChain(p, v));

        return d;
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

    Data queryEdgeChain(int anc, int u) {
        Data ret = NULL_VALUE;
        while (u != anc) {
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                ret = SegmentTreeSPU::combine(st.query(l, r), ret);
                u = p;
            } else {
                int r = stIdx[u];
                ret = SegmentTreeSPU::combine(st.query(r, r), ret);
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
int N, M, K;
struct Node {
    int x;
    uint64_t y;
} nodes[MAXN];

uint64_t ans;

void dp(const Data &d,
        int x, int y, uint64_t z, int k, bool clamped) {
    if (k == -1) return;
    int zk = (z >> k) & 1;
    if (!clamped || zk) {
        if (((d.b>>k)&1) > ((d.a>>k)&1)) {
            ans |= (uint64_t(1) << k);
            dp(d, x, y, z, k-1, clamped);
        } else {
            ans |= (d.a & (uint64_t(1)<< k));
            dp(d, x, y, z, k-1, false);
        }
    } else {
        ans |= (d.a & (uint64_t(1)<< k));
        dp(d, x, y, z, k-1, true);
    }
}

void debug(HeavyLightDecomposition &hld) {
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            Data d = hld.queryNode(u, v);
            for (int k = 0; k < K; k++) {
                printf("k=%d\n", k);
                printf("u=%d v=%d %llu %llu %llu %llu\n", u+1, v+1,
                       (d.a>>k)&1, (d.b>>k)&1, (d.c>>k)&1, (d.d>>k)&1);
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &N, &M, &K);
    HeavyLightDecomposition hld(N, K);
    for (int i = 0; i < N; i++) {
        scanf("%d%llu", &nodes[i].x, &nodes[i].y);
    }
    for (int i = 0;  i < N-1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        hld.addEdge(x, y);
    }
    hld.decompose();
    for (int i = 0; i < N; i++) {
        hld.updateNode(i, nodes[i].x, nodes[i].y);
    }

    for (int i = 0; i < M; i++) {
        int q, x, y;
        uint64_t z;
        scanf("%d%d%d%llu", &q, &x, &y, &z);
        if (q == 1) {
            ans = 0;
            x--; y--;
            //debug(hld);
            Data d = hld.queryNode(x, y);
            dp(d, x, y, z, K-1, true);
            printf("%llu\n", ans);
        } else {
            x--;
            hld.updateNode(x, y, z);
            //debug(hld);
        }
    }
    return 0;
}
