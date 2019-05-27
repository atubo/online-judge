// https://www.luogu.org/problemnew/show/P3345
// [ZJOI2015]幻想乡战略游戏

#include <bits/stdc++.h>
using namespace std;

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

    struct Node {
        int gc; // child on the gravity tree
        int c; // child on the original tree
        int wt;
    };

    GravityTree(int n): fa_(n), n_(n), out_edges_(n), gt_edges_(n) {
        alloc();
    }

    ~GravityTree() {
        dealloc();
    }

    int solve(int u) {
        dfs1(u, -1);
        if (sz_[u] == 1) {
            cut_[u] = true;
            fa_[u].push_back({u, 0, -1});
            return u;
        }

        tot_ = sz_[u];
        miv_ = INF;
        dfs2(u, -1);
        cut_[rt_] = true;
        fa_[rt_].push_back({rt_, 0, -1});
        int ret = rt_;

        for (int i = 0; i < (int)out_edges_[rt_].size(); i++) {
            int v = out_edges_[rt_][i].to;
            int w = out_edges_[rt_][i].wt;
            if (cut_[v]) continue;
            dep_[v] = w;
            dfs3(v, rt_, rt_, i);
        }
        for (const auto &e: out_edges_[rt_]) {
            int v = e.to;
            if (!cut_[v]) {
                int child = solve(v);
                gt_edges_[ret].push_back(Node{child, v, e.wt});
            }
        }
        return ret;
    }

    void addEdge(int u, int v, int w) {
        out_edges_[u].push_back({v, w});
        out_edges_[v].push_back({u, w});
    }

    int64_t cal(int now, int xld, int len) {
        int64_t ret = 1LL * d_[now] * len;
        for (const auto &node: gt_edges_[now]) {
            if (node.gc != xld) {
                ret += sumf_[node.gc];
                ret += 1LL * sumd_[node.gc] * len;
            }
        }
        return ret;
    }

    void change(int now, int to, int delta) {
        d_[now] += delta;
        for (int i = (int)fa_[now].size()-1; i >= 0; i--) {
            int u = fa_[now][i].f;
            if (u == to) break;
            sumd_[u] += delta;
            if (i > 0) {
                int64_t d = fa_[now][i-1].dist;
                sumf_[u] += 1LL * delta * d;
            }
        }
    }

    int64_t query(int now) {
        int64_t ans = 0;
        for (const auto &edge: gt_edges_[now]) {
            if (sumd_[edge.gc]*2 > sumd_[now]) {
                int64_t ret = cal(now, edge.gc, edge.wt);
                int delta = sumd_[now] - sumd_[edge.gc];
                change(edge.c, now, delta);
                ret += query(edge.gc);
                change(edge.c, now, -delta);
                return ret;
            }
            ans += sumf_[edge.gc];
        }
        return ans;
    }

    vector<vector<Dist>> fa_;
private:
    static const int INF = 0x3F3F3F3F;
    const int n_;
    vector<vector<Edge>> out_edges_;
    vector<vector<Node>> gt_edges_;
    int *sz_;
    bool *cut_;
    int tot_;
    int miv_;
    int rt_;
    int *dep_;
    int *d_;
    int *sumd_;
    int64_t *sumf_;

    void alloc() {
        sz_ = new int[n_]{};
        cut_ = new bool[n_]{};
        dep_ = new int[n_]{};
        d_ = new int[n_]{};
        sumd_ = new int[n_]{};
        sumf_ = new int64_t[n_]{};
    }

    void dealloc() {
        delete[] sz_;
        delete[] cut_;
        delete[] dep_;
        delete[] d_;
        delete[] sumd_;
        delete[] sumf_;
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

int main() {
    scanf("%d%d", &N, &Q);
    GravityTree gt(N);
    for (int i = 0; i < N-1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        gt.addEdge(a, b, c);
    }
    int root = gt.solve(0);

    for (int i = 0; i < Q; i++) {
        int u, e;
        scanf("%d%d", &u, &e);
        u--;
        gt.change(u, -1, e);
        printf("%ld\n", gt.query(root));
    }
    return 0;
}
