// https://www.luogu.org/problemnew/solution/P3241
// [HNOI2015]开店

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1.5e5+10;

struct Data {
    int val;
    int64_t sz;
    int64_t sv;
    bool operator < (const Data &other) const {
        if (val != other.val) return val < other.val;
        if (sz != other.sz) return sz < other.sz;
        return sv < other.sv;
    }
};

vector<Data> ans[MAXN][3];
int X[MAXN];

class GravityTree {
public:
    struct Dist {
        int f;
        int64_t dist;
        int br;

        bool operator == (const Dist &other) const {
            return f == other.f &&
                dist == other.dist &&
                br == other.br;
        }
    };

    struct Edge {
        int to;
        int wt;
    };

    GravityTree(int n): fa_(n), n_(n), out_edges_(n) {
        alloc();
    }

    ~GravityTree() {
        dealloc();
    }

    void solve(int u) {
        dfs1(u, -1);
        if (sz_[u] == 1) {
            cut_[u] = true;
            fa_[u].push_back({u, 0, -1});
            return;
        }

        tot_ = sz_[u];
        miv_ = INF;
        dfs2(u, -1);
        cut_[rt_] = true;
        fa_[rt_].push_back({rt_, 0, -1});

        for (int i = 0; i < (int)out_edges_[rt_].size(); i++) {
            int v = out_edges_[rt_][i].to;
            int w = out_edges_[rt_][i].wt;
            if (cut_[v]) continue;
            dep_[v] = w;
            dfs3(v, rt_, rt_, i);
            ans[rt_][i].push_back({INF, 0, 0});
            sort(ans[rt_][i].begin(), ans[rt_][i].end());
            for (int j = ans[rt_][i].size()-2; j >= 0; j--) {
                ans[rt_][i][j].sz += ans[rt_][i][j+1].sz;
                ans[rt_][i][j].sv += ans[rt_][i][j+1].sv;
            }
        }
        for (const auto &e: out_edges_[rt_]) {
            int v = e.to;
            if (!cut_[v]) solve(v);
        }
    }

    void addEdge(int u, int v, int w) {
        out_edges_[u].push_back({v, w});
        out_edges_[v].push_back({u, w});
    }

    int64_t query(int u, int l, int r) {
        int64_t res = 0;
        for (int i = fa_[u].size()-1; i >= 0; i--) {
            int f = fa_[u][i].f;
            for (int br = 0; br <= 2; br++) {
                if (br == fa_[u][i].br || ans[f][br].empty()) continue;
                auto L = lower_bound(ans[f][br].begin(),
                                     ans[f][br].end(),
                                     Data{l, 0, 0});
                auto R = upper_bound(ans[f][br].begin(),
                                     ans[f][br].end(),
                                     Data{r+1, 0, 0});
                res += fa_[u][i].dist * (L->sz - R->sz) +
                    L->sv - R->sv;
            }
            if (l <= X[f] && X[f] <= r) {
                res += fa_[u][i].dist;
            }
        }
        return res;
    }

    vector<vector<Dist>> fa_;
private:
    static const int INF = 0x3F3F3F3F;
    const int n_;
    vector<vector<Edge>> out_edges_;
    int *sz_;
    bool *cut_;
    int tot_;
    int miv_;
    int rt_;
    int *dep_;

    void alloc() {
        sz_ = new int[n_]{};
        cut_ = new bool[n_]{};
        dep_ = new int[n_]{};
    }

    void dealloc() {
        delete[] sz_;
        delete[] cut_;
        delete[] dep_;
    }

    void dfs1(int u, int f) {
        sz_[u] = 1;
        for (const auto &e: out_edges_[u]) {
            if (e.to != f && !cut_[u]) {
                dfs1(e.to, u);
                sz_[u] += sz_[e.to];
            }
        }
    }

    void dfs2(int u, int f) {
        int mav = tot_ - sz_[u];
        for (const auto &e: out_edges_[u]) {
            int v = e.to;
            if (v != f && !cut_[v]) {
                dfs2(v, u);
                mav = max(mav, sz_[v]);
            }
        }
        if (miv_ > mav) {
            miv_ = mav;
            rt_ = u;
        }
    }

    void dfs3(int u, int f, int g, int br) {
        // f is the father on the original tree
        // g is the father on the gravity tree
        // br is the branch number on the gravity tree
        fa_[u].push_back({g, dep_[u], br});
        ans[g][br].push_back({X[u], 1, dep_[u]});
        for (const auto &e: out_edges_[u]) {
            int v = e.to;
            int w = e.wt;
            if (v != f && !cut_[v]) {
                dep_[v] = dep_[u] + w;
                dfs3(v, u, g, br);
            }
        }
    }
};

int N, Q;
int64_t A;

int main() {
    scanf("%d%d%ld", &N, &Q, &A);
    for (int i = 0; i < N; i++) {
        scanf("%d", &X[i]);
    }
    GravityTree gt(N);
    for (int i = 0; i < N-1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        gt.addEdge(a, b, c);
    }
    gt.solve(0);

    int64_t last = 0;
    for (int i = 0; i < Q; i++) {
        int u;
        int64_t a, b;
        scanf("%d%ld%ld", &u, &a, &b);
        u--;
        int64_t l = (a + last) % A;
        int64_t r = (b + last) % A;
        if (l > r) swap(l, r);
        last = gt.query(u, l, r);
        printf("%ld\n", last);
    }

    return 0;
}
