// https://www.luogu.org/problemnew/solution/P2664
// 树上游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
int V[MAXN];

class GravityTree {
public:
    GravityTree(int n): n_(n), out_edges_(n) {
        alloc();
    }

    ~GravityTree() {
        dealloc();
    }

    void solve(int u) {
        dfs1(u, -1);
        if (sz_[u] == 1) {
            cut_[u] = true;
            return;
        }

        tot_ = sz_[u];
        miv_ = INF;
        dfs2(u, -1);
        cut_[rt_] = true;

        count(rt_, -1);
        for (int v: out_edges_[rt_]) {
            if (!cut_[v]) solve(v);
        }
    }

    void addEdge(int u, int v) {
        out_edges_[u].push_back(v);
        out_edges_[v].push_back(u);
    }

    int64_t *ans_;

private:
    static const int INF = 0x3F3F3F3F;
    const int n_;
    vector<vector<int>> out_edges_;
    int *sz_;
    bool *cut_;
    int *cnt_;
    int *color_;
    int64_t sum_ = 0;
    int num_ = 0;
    int sz_other_ = 0;
    int tot_;
    int miv_;
    int rt_;

    void alloc() {
        sz_ = new int[n_]{};
        cut_ = new bool[n_]{};
        cnt_ = new int[MAXN]{};
        color_ = new int[MAXN]{};
        ans_ = new int64_t[n_]{};
    }

    void dealloc() {
        delete[] sz_;
        delete[] cut_;
        delete[] cnt_;
        delete[] color_;
        delete[] ans_;
    }

    void dfs1(int u, int f) {
        sz_[u] = 1;
        for (int v: out_edges_[u]) {
            if (v != f && !cut_[u]) {
                dfs1(v, u);
                sz_[u] += sz_[v];
            }
        }
    }

    void dfs2(int u, int f) {
        int mav = tot_ - sz_[u];
        for (int v: out_edges_[u]) {
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

    void dfs3(int u, int f) {
        // f is the father on the original tree
        sz_[u] = 1;
        cnt_[V[u]]++;
        for (int v: out_edges_[u]) {
            if (v != f && !cut_[v]) {
                dfs3(v, u);
                sz_[u] += sz_[v];
            }
        }
        if (cnt_[V[u]] == 1) {
            sum_ += sz_[u];
            color_[V[u]] += sz_[u];
        }
        cnt_[V[u]]--;
    }

    void change(int u, int f, int value) {
        int c = V[u];
        cnt_[c]++;
        for (int v: out_edges_[u]) {
            if (v != f && !cut_[v]) {
                change(v, u, value);
            }
        }
        if (cnt_[c] == 1) {
            sum_ += 1LL * sz_[u] * value;
            color_[c] += 1LL * sz_[u] * value;
        }
        cnt_[c]--;
    }

    void dfs4(int u, int f) {
        int c = V[u];
        cnt_[c]++;
        if (cnt_[c] == 1) {
            sum_ -= color_[c];
            num_++;
        }
        ans_[u] += sum_ + 1LL * num_ * sz_other_;
        for (int v: out_edges_[u]) {
            if (v != f && !cut_[v]) {
                dfs4(v, u);
            }
        }
        if (cnt_[c] == 1) {
            sum_ += color_[c];
            num_--;
        }
        cnt_[c]--;
    }

    void clear(int u, int f) {
        int c = V[u];
        cnt_[c] = color_[c] = 0;
        for (int v: out_edges_[u]) {
            if (v != f && !cut_[v]) {
                clear(v, u);
            }
        }
    }

    void count(int u,  int f) {
        int c = V[u];
        dfs3(u, f);
        ans_[u] += sum_ - color_[c] + sz_[u];
        for (int v: out_edges_[u]) {
            if (v != f && !cut_[v]) {
                cnt_[c]++;
                sum_ -= sz_[v];
                color_[c] -= sz_[v];
                change(v, u, -1);
                cnt_[c]--;
                sz_other_ = sz_[u] - sz_[v];
                dfs4(v, u);
                cnt_[c]++;
                sum_ += sz_[v];
                color_[c] += sz_[v];
                change(v, u, 1);
                cnt_[c]--;
            }
        }
        sum_ = num_ = 0;
        clear(u, f);
    }
};

int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }
    GravityTree gt(N);
    for (int i = 0; i < N-1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        gt.addEdge(x, y);
    }
    gt.solve(0);

    for (int i = 0; i < N; i++) {
        printf("%ld\n", gt.ans_[i]);
    }

    return 0;
}
