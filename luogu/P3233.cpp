// https://www.luogu.org/problemnew/show/P3233
// [HNOI2014]世界树

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300010;
int vfa[MAXN];

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

int father_[MAXN][20];
int ancestor(int u, int k) {
    for (int i = 0; k; ++i,k>>=1) {
        if (k&1) u = father_[u][i];
    }
    return u;
}

class VirtualTree {
public:
    Graph vg;

private:
    int MAXB_;
    int sz_;
    int N_, root_;
    int *depth_;
    //int **father_;
    int *dfn_;
    vector<int> stk_;

    Graph g_;

public:
    VirtualTree(int n, int r): vg(n, n-1), N_(n), root_(r), g_(n, n-1) {
        MAXB_ = int(log2(N_) + 1.5);
        sz_ = 0;

        depth_ = new int[N_]{};
#if 0
        father_ = new int*[N_]{};
        for (int i = 0; i < N_; i++) {
            father_[i] = new int[MAXB_]{};
            memset(father_[i], -1, MAXB_ * sizeof(int));
        }
#endif
        memset(father_, -1, sizeof(father_));
        dfn_ = new int[N_]{};
    }

    ~VirtualTree() {
        delete[] depth_;
        delete[] dfn_;

#if 0
        for (int i = 0; i < N_; i++) {
            delete[] father_[i];
        }
        delete[] father_;
#endif
    }

    // only father to child edges are allowed
    void addEdge(int u, int v) {
        g_.addEdge(u, v);
    }

    void preCompute() {
        dfs(root_, root_, 0);

        binaryLift();

        stk_.resize(N_);
    }

    void dfs(int x, int f, int d) {
        dfn_[x] = sz_++;
        depth_[x] = d;
        father_[x][0] = f;
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int u = g_.E[eidx].to;
            if (u != f) dfs(u, x, d+1);
        }
    }

#if 0
    int ancestor(int u, int k) const {
        for (int i = 0; k; ++i,k>>=1) {
            if (k&1) u = father_[u][i];
        }
        return u;
    }
#endif

    void binaryLift() {
        for (int j = 1; j < MAXB_; j++) {
            for (int i = 0; i < N_; i++) {
                if (father_[i][j-1] != -1) {
                    father_[i][j] = father_[father_[i][j-1]][j-1];
                }
            }
        }
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

    int buildVirtualTree(vector<int>& vertices, int k) {
        vg.reset();

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

        return cnt;
    }

    void addVirtualEdge(int u, int v) {
        vg.addEdge(u, v);
        vfa[v] = u;
    }
};
int N, Q;
int depth[MAXN], dfn[MAXN], size[MAXN];
int currDfn;

struct Dist {
    int d, u;
    bool operator < (const Dist &other) const {
        if (d < other.d) return true;
        if (d > other.d) return false;
        return u < other.u;
    }
} nearest[MAXN];

bool dfncmp(const int u, const int v) {
    return dfn[u] < dfn[v];
}

void dfs1(const Graph &g, VirtualTree &vt, int u, int fa, int d) {
    depth[u] = d;
    dfn[u] = currDfn++;
    size[u] = 1;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            vt.addEdge(u, v);
            dfs1(g, vt, v, u, d+1);
            size[u] += size[v];
        }
    }
}

void top2(Dist &d0, Dist &d1, const Dist &d) {
    if (d < d0) {
        d1 = d0;
        d0 = d;
    } else if (d < d1) {
        d1 = d;
    }
}

int dfs2(const VirtualTree &vt, int u,
          const Dist &faDist,
          const vector<bool> &real,
          vector<Dist> &dominate,
          vector<int> &ans) {
    Dist d0 = faDist;
    Dist d1 = {INT_MAX/2, -1};
    if (real[u]) top2(d0, d1, {0, u});
    for (int eidx = vt.vg.head[u]; ~eidx; eidx = vt.vg.E[eidx].next) {
        int v = vt.vg.E[eidx].to;
        Dist d = nearest[v];
        top2(d0, d1, {d.d + depth[v] - depth[u], d.u});
    }
    dominate[u] = d0;

    int uu = dominate[u].u;
    int subTotal = 0;

    for (int eidx = vt.vg.head[u]; ~eidx; eidx = vt.vg.E[eidx].next) {
        int v = vt.vg.E[eidx].to;
        Dist d = nearest[v];
        if (d.u != d0.u) {
            subTotal += dfs2(vt, v, {d0.d + depth[v] - depth[u], d0.u},
                 real, dominate, ans);
        } else {
            subTotal += dfs2(vt, v, {d1.d + depth[v] - depth[u], d1.u},
                 real, dominate, ans);
        }
    }

    int oldAns = ans[uu];
    ans[uu] += size[u] - subTotal;

    int fa = vfa[u];
    if (fa != -1) {
        Dist fad = dominate[fa];
        int t = depth[u] + depth[fa] + dominate[u].d - fad.d;
        int dmid = t / 2 + ( (t&1) || fad.u < uu);
        int v = ancestor(u, depth[u] - dmid);
        ans[uu] += size[v] - size[u];
    } else {
        ans[uu] += size[0] - size[u];
    }
    return subTotal + ans[uu] - oldAns;
}

int dfs3(const VirtualTree &vt, int u, const vector<Dist> &dominate,
          vector<int> &ans) {
    int uu = dominate[u].u;
    int subTotal = 0;
    for (int eidx = vt.vg.head[u]; ~eidx; eidx = vt.vg.E[eidx].next) {
        int v = vt.vg.E[eidx].to;
        subTotal += dfs3(vt, v, dominate, ans);
    }

    int oldAns = ans[uu];
    ans[uu] += size[u] - subTotal;

    int fa = vfa[u];
    if (fa != -1) {
        Dist fad = dominate[fa];
        int t = depth[u] + depth[fa] + dominate[u].d - fad.d;
        int dmid = t / 2 + ( (t&1) || fad.u < uu);
        int v = ancestor(u, depth[u] - dmid);
        ans[uu] += size[v] - size[u];
    } else {
        ans[uu] += size[0] - size[u];
    }
    return subTotal + ans[uu] - oldAns;
}



void solve(const VirtualTree &vt, const vector<int> &idx,
           vector<int> &places, const vector<bool> &real,
           int sz) {
    sort(places.begin(), places.begin() + sz, dfncmp);

    //vector<Dist> nearest(N);
    memset(nearest, 0, sizeof(nearest));
    for (int i = sz-1; i >= 0; i--) {
        int u = places[i];
        if (real[u]) {
            nearest[u] = {0, u};
            continue;
        }
        nearest[u] = {INT_MAX, -1};
        for (int eidx = vt.vg.head[u]; ~eidx; eidx = vt.vg.E[eidx].next) {
            int v = vt.vg.E[eidx].to;
            int d = depth[v] - depth[u] + nearest[v].d;
            Dist curr = {d, nearest[v].u};
            nearest[u] = min(nearest[u], curr);
        }
    }

    vector<Dist> dominate(N);
    vector<int> ans(N);
    dfs2(vt, places[0], {INT_MAX/2, -1}, real, dominate, ans);

    //dfs3(vt, places[0], dominate, ans);

    for (int x: idx) {
        printf("%d ", ans[x]);
    }
    printf("\n");
}

template<typename T>void read(T &x){
    T f=1;char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
    for(x=0;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
    x*=f;
}

int main() {
    scanf("%d", &N);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int x, y;
        //scanf("%d%d", &x, &y);
        read(x); read(y);
        x--; y--;
        g.addEdge(x, y);
        g.addEdge(y, x);
    }
    VirtualTree vt(N, 0);
    dfs1(g, vt, 0, 0, 0);
    vt.preCompute();

    //scanf("%d", &Q);
    read(Q);
    vector<int> places(N);
    vector<bool> real(N);
    for (int q = 0; q < Q; q++) {
        fill(places.begin(), places.end(), -1);
        fill(real.begin(), real.end(), false);
        memset(vfa, -1, sizeof(vfa));
        int m;
        //scanf("%d", &m);
        read(m);
        vector<int> idx(m);
        for (int i = 0; i < m; i++) {
            //scanf("%d", &places[i]);
            read(places[i]);
            places[i]--;
            real[places[i]] = true;
            idx[i] = places[i];
        }
        int cnt = vt.buildVirtualTree(places, m);
        solve(vt, idx, places, real, cnt);
    }

    return 0;
}
