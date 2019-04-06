// https://www.luogu.org/problemnew/show/P3401
// 洛谷树

#include <bits/stdc++.h>
using namespace std;

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) (x < y ? x : y)

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
        int *s_, *x_, *y_, *z_;

    public:
        SegmentTree(int N_): N(N_) {
            s_ = new int[4*N]{};
            x_ = new int[4*N]{};
            y_ = new int[4*N]{};
            z_ = new int[4*N]{};
        }

        ~SegmentTree() {
            delete[] s_;
            delete[] x_;
            delete[] y_;
            delete[] z_;
        }

        void update(int t, int a) {
            update(1, t, 0, N-1, a);
        }

        void query(int a, int b, int &x, int &y, int &z, int &s) {
            return query(1, a, b, 0, N-1, x, y, z, s);
        }

        void merge(int x1, int y1, int z1, int s1, int n1,
                   int x2, int y2, int z2, int s2, int n2,
                   int &x, int &y, int &z, int &s) {
            z = z1 + z2 + x1*(n2-y2) + y2*(n1-x1);
            y = y1 + (s1 == 0 ? y2 : n2-y2);
            x = x2 + (s2 == 0 ? x1 : n1-x1);
            s = s1 ^ s2;
        }


    private:
        void update(int k, int t, int l, int r, int a) {
            if (l == r) {
                s_[k] = x_[k] = y_[k] = z_[k] = t;
                return;
            }
            int lc = 2*k, rc = 2*k + 1;
            int mid = (l + r) / 2;
            if (a <= mid) update(lc, t, l, mid, a);
            else          update(rc, t, mid+1, r, a);

            int n1 = mid + 1 - l;
            int n2 = r - mid;
            merge(x_[lc], y_[lc], z_[lc], s_[lc], n1,
                  x_[rc], y_[rc], z_[rc], s_[rc], n2,
                  x_[k], y_[k], z_[k], s_[k]);
        }

        void query(int k, int a, int b, int l, int r,
                   int &x, int &y, int &z, int &s) {
            if (!k || b < l || a > r) {
                x = y = z = s = 0;
                return;
            }
            if (a <= l && r <= b) {
                x = x_[k];
                y = y_[k];
                z = z_[k];
                s = s_[k];
                return;
            }
            int mid = (l + r) / 2;
            int x1 = 0, y1 = 0, z1 = 0, s1 = 0;
            int x2 = 0, y2 = 0, z2 = 0, s2 = 0;
            if (a <= mid) query(2*k, a, b, l, mid, x1, y1, z1, s1);
            if (mid < b)  query(2*k+1, a, b, mid+1, r, x2, y2, z2, s2);
            int n1 = MAX(0, mid-MAX(l,a)+1);
            int n2 = MAX(0, MIN(b,r)-mid);
            if (n1 == 0) {
                x = x2; y = y2; z = z2; s = s2;
            } else if (n2 == 0) {
                x = x1; y = y1; z = z1; s = s1;
            } else {
                merge(x1, y1, z1, s1, n1, x2, y2, z2, s2, n2,
                      x, y, z, s);
            }
        }
    };

public:
    const int N;
    Graph g;
    SegmentTree *st[10];
    vector<int> size;
    vector<int> dep;
    vector<int> rev;    // node to father-edge
    vector<int> heavy;
    vector<int> stIdx;    // node to segment tree index
    vector<int> fa; // father along heavy chain, -1 is father-edge isn't heavy
    vector<int> top;
    int root;
    int Seg_size;

    HeavyLightDecomposition(int N_): N(N_), g(N_) {
        for (int i = 0; i < 10; i++) {
            st[i] = new SegmentTree(N);
        }
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        stIdx.resize(N, -1);
        fa.resize(N, -1);
        top.resize(N);

        root = 0;
        Seg_size = 0;   // segment tree is 0-indexed
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

    void updateEdge(int u, int t) {
        int r = stIdx[u];
        for (int d = 0; d < 10; d++) {
            st[d]->update((t>>d)&1, r);
        }
    }

    int64_t queryEdge(int u, int v) {
        int64_t ret = 0;
        int p = lca(u, v);
        for (int d = 0; d < 10; d++) {
            int x1, y1, z1, s1;
            int n1 = queryEdgeChain(p, u, d, x1, y1, z1, s1);
            int x2, y2, z2, s2;
            int n2 = queryEdgeChain(p, v, d, x2, y2, z2, s2);
            int x, y, z, s;
            st[d]->merge(y1, x1, z1, s1, n1, x2, y2, z2, s2, n2,
                         x, y, z, s);
            ret += (1LL*z) << d;
        }

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

    int queryEdgeChain(int anc, int u, int d,
                        int &x, int &y, int &z, int &s) {
        int x1 = 0, y1 = 0, z1 = 0, s1 = 0;
        int x2 = 0, y2 = 0, z2 = 0, s2 = 0, n2 = 0;
        x = y = z = s = 0;
        while (u != anc) {
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = stIdx[heavyChild(p)];
                int r = stIdx[u];
                st[d]->query(l, r, x1, y1, z1, s1);
                u = p;
                st[d]->merge(x1, y1, z1, s1, r-l+1,
                             x2, y2, z2, s2, n2,
                             x, y, z, s);
                x2 = x; y2 = y; z2 = z; s2 = s; n2 += r-l+1;
            } else {
                int r = stIdx[u];
                st[d]->query(r, r, x1, y1, z1, s1);
                int fe = rev[u];
                u = g.E[fe].to;
                st[d]->merge(x1, y1, z1, s1, 1,
                             x2, y2, z2, s2, n2,
                             x, y, z, s);
                x2 = x; y2 = y; z2 = z; s2 = s; n2++;
            }
        }
        return n2;
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
struct Edge {
    int u, v, w;
} E[MAXN];

int main() {
    scanf("%d%d", &N, &Q);
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N-1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        E[i] = {u, v, w};
        hld.addEdge(u, v);
    }
    hld.decompose();
    for (int i = 0; i < N-1; i++) {
        int u = E[i].u;
        int v = E[i].v;
        int w = E[i].w;
        if (hld.dep[u] > hld.dep[v]) swap(u, v);
        hld.updateEdge(v, w);
    }

    for (int i = 0; i < Q; i++) {
        int op, u, v, w;
        scanf("%d%d%d", &op, &u, &v);
        u--; v--;
        if (op == 1) {
            printf("%ld\n", hld.queryEdge(u, v));
        } else {
            scanf("%d", &w);
            if (hld.dep[u] > hld.dep[v]) swap(u, v);
            hld.updateEdge(v, w);
        }
    }

    return 0;
}
