// https://www.luogu.org/problemnew/show/P4103
// [HEOI2014]大工程

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
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[M]{};
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

    void reset() {
        fill(head.begin(), head.end(), -1);
        eidx = 0;
    }
};

const int MAXN = 1000010, inf = 1e9;
int nodes[MAXN];

class VirtualTree {
public:
    Graph vg;
    vector<int> depth_;

private:
    int MAXB_;
    int sz_;
    int N_, root_;
    vector<vector<int> > father_;
    vector<int> dfn_;
    vector<int> stk_;

    Graph g_;

public:
    VirtualTree(int n, int r): vg(n, 2*n), N_(n), root_(r), g_(n, n-1) {
        MAXB_ = int(log2(N_) + 1.5);
        sz_ = 0;
    }

    // only father to child edges are allowed
    void addEdge(int u, int v) {
        g_.addEdge(u, v);
    }

    void preCompute() {

        depth_.resize(N_);
        father_.resize(N_);
        dfn_.resize(N_);
        for (int i = 0; i < N_; i++) {
            father_[i].resize(MAXB_, -1);
        }

        dfs(root_, -1, 0);

        stk_.resize(N_+5);
    }

    void buildVirtualTree(int k) {
        //vg.reset();

#if 0
        sz_ = 0;
        int cnt = k;
        sort(vertices.begin(), vertices.begin()+k, CmpByDfn(*this));

        for (int i = 0; i < k; i++) {
            int u = vertices[i];
            int lca = (sz_ > 0 ? findLCA(u, stk_[sz_-1]) : u);
            if (sz_ == 0 || lca == stk_[sz_-1]) stk_[sz_++] = u;
            else {
                while (sz_ - 2 >= 0 && depth_[stk_[sz_-2]] >= depth_[lca]) {
                    addVirtualEdge(stk_[sz_-2], stk_[sz_-1]);
                    sz_--;
                }

                if (stk_[sz_-1] != lca) {
                    addVirtualEdge(lca, stk_[--sz_]);
                    stk_[sz_++] = lca;
                    vertices[cnt++] = lca;
                }

                stk_[sz_++] = u;
            }
        }

        for (int i = 0; i < sz_-1; i++) {
            addVirtualEdge(stk_[i], stk_[i+1]);
        }
#else
        sort(nodes, nodes+k, CmpByDfn(*this));
        stk_[0] = root_;
        int top = 0;
        for (int i = 0; i < k; i++) {
            int x = nodes[i], p = findLCA(stk_[top], x);
            while (depth_[p] < depth_[stk_[top]]) {
                if (depth_[p] >= depth_[stk_[top-1]]) {
                    addVirtualEdge(p, stk_[top]);
                    if (stk_[--top] != p) {
                        stk_[++top] = p;
                        //nodes[cnt++] = p;
                    }
                    break;
                }
                addVirtualEdge(stk_[top-1], stk_[top]);
                top--;
            }
            if (stk_[top] != x) stk_[++top] = x;
        }
        while (top > 0) {
            addVirtualEdge(stk_[top-1], stk_[top]);
            top--;
        }
#endif
    }

private:
    void dfs(int x, int f, int d) {
        dfn_[x] = sz_++;
        depth_[x] = d;
        father_[x][0] = f;
        for (int i = 0; ~father_[x][i]; i++) {
            father_[x][i+1] = father_[father_[x][i]][i];
        }
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int u = g_.E[eidx].to;
            if (u != f) {
                dfs(u, x, d+1);
            }
        }
    }

    int ancestor(int u, int k) {
        for (int i = 0; k; ++i, k>>=1) {
            if (k&1) u = father_[u][i];
        }
        return u;
    }

    int findLCA(int u, int v) {
        if (depth_[u] < depth_[v]) swap(u, v);
        u = ancestor(u, depth_[u] - depth_[v]);

        if (u == v) return u;

        for (int b = MAXB_-1; b >= 0; b--) {
            if (father_[u][b] == -1) continue;
            if (father_[u][b] != father_[v][b]) {
                u = father_[u][b];
                v = father_[v][b];
            }
        }
        return father_[u][0];
    }

    struct CmpByDfn {
        CmpByDfn(const VirtualTree& t): m_t(t) {}
        const VirtualTree& m_t;

        bool operator()(int i, int j) {
            return m_t.dfn_[i] < m_t.dfn_[j];
        }
    };


    void addVirtualEdge(int u, int v) {
        vg.addEdge(u, v);
    }
};

int N, Q;
bool fg[MAXN];
int sz[MAXN];
int64_t totPrice;
int shallow[MAXN];
int deep[MAXN];
int amax, amin;

struct Item {
    int u, fa;
};

void dfs1(const Graph &g, VirtualTree &vt, int u, int fa) {
    stack<Item> s;
    s.push({u, fa});
    while (!s.empty()) {
        Item x = s.top();
        s.pop();
        for (int eidx = g.head[x.u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v != x.fa) {
                vt.addEdge(x.u, v);
                s.push({v, x.u});
            }
        }
    }
}

void dfs2(VirtualTree &vt, int u, int k) {
    sz[u] = fg[u];
    deep[u] = (fg[u] ? vt.depth_[u] : -inf);
    shallow[u] = (fg[u] ? vt.depth_[u] : inf);
    for (int eidx = vt.vg.head[u]; ~eidx; eidx = vt.vg.E[eidx].next) {
        int v = vt.vg.E[eidx].to;
        dfs2(vt, v, k);
        sz[u] += sz[v];
        int64_t d = vt.depth_[v] - vt.depth_[u];
        totPrice += d * sz[v] * (k - sz[v]);
        amax = max(amax, deep[u] + deep[v] - 2*vt.depth_[u]);
        amin = min(amin, shallow[u] + shallow[v] - 2*vt.depth_[u]);
        deep[u] = max(deep[u], deep[v]);
        shallow[u] = min(shallow[u], shallow[v]);
    }
    vt.vg.head[u] = -1;
}

void solve(VirtualTree &vt, int k) {
    for (int i = 0; i < k; i++) {
        fg[nodes[i]] = true;
    }
#if 0
    int cnt = vt.buildVirtualTree(k);
    int root = -1, minDep = INT_MAX;
    for (int i = 0; i < cnt; i++) {
        int u = nodes[i];
        int d = vt.depth_[u];
        if (d < minDep) {
            minDep = d;
            root = u;
        }
    }
#endif
    vt.buildVirtualTree(k);

    int root = 0;
    amax = -inf, amin = inf;
    totPrice = 0;
    dfs2(vt, root, k);
    printf("%lld %d %d\n", totPrice, amin, amax);

    for (int i = 0; i < k; i++) {
        fg[nodes[i]] = false;
    }
}


int main() {
    scanf("%d", &N);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
        g.addEdge(b, a);
    }
    VirtualTree vt(N, 0);
    dfs1(g, vt, 0, -1);
    vt.preCompute();

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &nodes[j]);
            nodes[j]--;
        }
        if (k > 0) solve(vt, k);
        else printf("0 0 0\n");
    }
    return 0;
}
